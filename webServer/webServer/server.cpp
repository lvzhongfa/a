#include "server.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/epoll.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <iostream>
#include <sys/stat.h>
#include <dirent.h>
using namespace std;

const int MAX = 1024;

int initListen(unsigned short port)
{
	// 1. 创建监听套接字
	int lfd = socket(AF_INET, SOCK_STREAM, 0); 
	if (lfd == -1)
	{
		perror("socket");
		return -1;
	}

	// 1.5 设置端口复用
	int opt = 1;
	setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	// 2. 监听的lfd绑定本地的ip和port
	struct sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.s_addr = INADDR_ANY;
	int ret = bind(lfd, (struct sockaddr*)&addr, sizeof(addr));
	if (ret == -1)
	{
		perror("bind");
		return -1;
	}

	// 3. 设置监听
	ret = listen(lfd, 128);
	if (ret == -1)
	{
		perror("listen");
		return -1;
	}
	return lfd;
}

int epollRun(int lfd)
{
	// 1. 创建epoll树
	int epfd = epoll_create(100);
	if (epfd == -1)
	{
		perror("epoll_create");
		return -1;
	}

	// 2. 将监听的fd挂到树上
	struct epoll_event ev;
	ev.data.fd = lfd;
	ev.events = EPOLLIN;	// 检测读缓冲区
	int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, lfd, &ev);
	if (ret == -1)
	{
		perror("epoll_ctl");
		return -1;
	}

	// 3. 启动epoll
	struct epoll_event evs[MAX];
	while (1)
	{
		int num = epoll_wait(epfd, evs, MAX, -1);
		for (int i = 0; i < num; ++i)
		{
			int fd = evs[i].data.fd;
			// 有新连接
			if (fd == lfd)
			{
				// 接受连接
				acceptConn(lfd, epfd);
			}
			// 通信
			else
			{
				// 接收客户端发送的数据 -> 基于get的http请求
				recvHttpRequest(fd, epfd);
			}
		}
	}

	return 0;
}

int acceptConn(int lfd, int epfd)
{
	// 1. 接受连接
	int cfd = accept(lfd, NULL, NULL);
	if (cfd == -1)
	{
		perror("accept");
		return -1;
	}

	// 2. 设置cfd为非阻塞模式
	int flag = fcntl(cfd, F_GETFL);
	flag |= O_NONBLOCK;
	fcntl(cfd, F_SETFL, flag);

	// 3. 将cfd添加到树上
	struct epoll_event ev;
	ev.data.fd = cfd;
	ev.events = EPOLLIN | EPOLLET;	// 设置为边沿模式
	int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, cfd, &ev);
	if (ret == -1)
	{
		perror("epoll_ctl");
		return -1;
	}
	return 0;
}

int recvHttpRequest(int cfd, int epfd)
{
	// 1. cfd为非阻塞并且epoll为边沿模式, 循环读数据
	int len = 0, total = 0;
	char buf[128], recvMsg[4096];
	while ((len = read(cfd, buf, sizeof(buf))) > 0)
	{
		// 将buf中的数据拷贝到recvMsg
		memcpy(recvMsg + total, buf, len);
		total += len;
	}
	// 2. 当read/recv return -1 && errno == eagain
	if (len == -1)
	{
		if (errno == EAGAIN)
		{
			// 数据读完了
			// 取出请求行, 第一行, 结尾是\r\n
			char* pt = strstr(recvMsg, "\r\n");
			// 计算请求行的长度
			int reqLineLen = pt - recvMsg;
			recvMsg[reqLineLen] = '\0';
			// 解析请求行数据
			parseRequestLine(cfd, recvMsg);
		}
		else
		{
			perror("read");
			return -1;
		}
	}
	else if (len == 0)
	{
		// 客户端断开了连接
		cout << "client disconnect..." << endl;
		disconnect(cfd, epfd);
	}
	return 0;
}

int disconnect(int cfd, int epfd)
{
	// 将cfd从epoll树上删除
	int ret = epoll_ctl(epfd, EPOLL_CTL_DEL, cfd, NULL);
	if (ret == -1)
	{
		perror("epoll_ctl");
		return -1;
	}
	close(cfd);

	return 0;
}

int parseRequestLine(int cfd, const char * reqLine)
{
	/*
		请求行数据格式:
		get /xxxxxxxxxxxx http/1.1
	*/
	char method[12], path[4096];
	sscanf(reqLine, "%[^ ] %[^ ]", method, path);
	cout << "requestLine: " << reqLine << endl;
	cout << "method: " << method << endl;
	cout << "path: " << path << endl;
	// 只处理get请求
	if (strcasecmp(method, "get") != 0)
	{
		cout << "客户端提交的是不是get请求, 忽略处理..." << endl;
		return -1;
	}

	/*
		path中的数据格式:
			/hello/index.html?user=zhang3&pwd=12345
			客户端向服务器请求的数据: -> 程序中要处理的数据格式
				/hello/index.html -> 文件
				/hello/			  -> 目录
				/				  -> 服务器提供的资源根目录
			客户端向服务器提交的数据:
				user=zhang3&pwd=12345
				当前程序中涉及不到提交数据的操作
	*/ 
	// 判断path中存储的是不是资源根目录
	// 指向要访问的资源的名字
	char* file = NULL;
	// path中存储的数据是被编码过的, 需要解码
	decodeMsg(path, path);
	cout << "解码之后的path数据: " << path << endl;
	if (strcmp(path, "/") == 0)
	{
		// 访问当前资源根目录
		file = "./";
	}
	else
	{
		// 访问资源根目录中的子目录或文件
		// /hello/   /hello/index.html /a.jpg
		file = path + 1;
	}
	// 判断文件的属性
	struct stat st;
	int ret = stat(file, &st);
	if (ret == -1)
	{
		perror("stat");
		// 客户端做了错误的请求, 返回404, 要求资源目录中要有404页面
		// 发送头数据
		sendRespondHead(cfd, 404, "not found", getFileType("404.html"), -1);
		// 发送回复的数据
		sendFile(cfd, "404.html");
		return -1;
	}
	// 服务器给客户端回复数据 -> http响应
	/*
		状态行
		响应头(消息报头)
		空行
		回复的数据

		http/1.1 200 ok
		Content-Type: 描述的是给客户端回复的数据(响应数据)的格式
		Content-Length: 给客户端回复的数据(响应数据)的长度

		数据块
	*/
	// 判断文件类型, 是不是目录
	if (S_ISDIR(st.st_mode))
	{
		// 遍历目录, 发送目录的文件名到客户端
		// 发送头数据
		sendRespondHead(cfd, 200, "OK", getFileType(".html"), -1);
		// 发送目录内容到客户端
		// 文件名   文件大小   
		sendDir(cfd, file);
	}
	else
	{
		// 读文件, 将文件内容发送给客户端
		// 发送头数据
		// 文件名: a.jpg a.html a.mp3 a.mp4
		sendRespondHead(cfd, 200, "OK", getFileType(file), (int)st.st_size);
		// 发送回复的数据
		sendFile(cfd, file);
	}

	return 0;
}

int sendRespondHead(int cfd, int status, const char* descr,
	const char* type, int len)
{
	char head[1024];
	// 状态行
	sprintf(head, "http/1.1 %d %s\r\n", status, descr);
	// 消息报头
	sprintf(head+strlen(head), "Content-Type:%s\r\n", type);
	sprintf(head+strlen(head), "Content-Length:%d\r\n", len);
	// 空行
	sprintf(head+strlen(head), "\r\n");
	// 发送数据
	write(cfd, head, strlen(head));

	return 0;
}

int sendFile(int cfd, const char* filename)
{
	// 1. 打开文件
	int fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("open");
		return -1;
	}
	// 2. 读文件并发送
	int len = 0;
	char buf[1024];
	while ((len = read(fd, buf, sizeof(buf))) > 0)
	{
		// 将读出的数据发送给客户端
		send(cfd, buf, len, 0);
		usleep(10);	// 微妙
	}
	// 3. 关闭文件
	close(fd);
	return 0;
}

// 通过文件名获取文件的类型
const char *getFileType(const char *name)
{
	// a.jpg a.mp4 a.html
	// 自右向左查找‘.’字符, 如不存在返回NULL
	const char* dot = strrchr(name, '.');
	if (dot == NULL)
		return "text/plain; charset=utf-8";	// 纯文本
	if (strcmp(dot, ".html") == 0 || strcmp(dot, ".htm") == 0)
		return "text/html; charset=utf-8";
	if (strcmp(dot, ".jpg") == 0 || strcmp(dot, ".jpeg") == 0)
		return "image/jpeg";
	if (strcmp(dot, ".gif") == 0)
		return "image/gif";
	if (strcmp(dot, ".png") == 0)
		return "image/png";
	if (strcmp(dot, ".css") == 0)
		return "text/css";
	if (strcmp(dot, ".au") == 0)
		return "audio/basic";
	if (strcmp(dot, ".wav") == 0)
		return "audio/wav";
	if (strcmp(dot, ".avi") == 0)
		return "video/x-msvideo";
	if (strcmp(dot, ".mov") == 0 || strcmp(dot, ".qt") == 0)
		return "video/quicktime";
	if (strcmp(dot, ".mpeg") == 0 || strcmp(dot, ".mpe") == 0)
		return "video/mpeg";
	if (strcmp(dot, ".vrml") == 0 || strcmp(dot, ".wrl") == 0)
		return "model/vrml";
	if (strcmp(dot, ".midi") == 0 || strcmp(dot, ".mid") == 0)
		return "audio/midi";
	if (strcmp(dot, ".mp3") == 0)
		return "audio/mpeg";
	if (strcmp(dot, ".ogg") == 0)
		return "application/ogg";
	if (strcmp(dot, ".pac") == 0)
		return "application/x-ns-proxy-autoconfig";

	return "text/plain; charset=utf-8";
}

int sendDir(int cfd, const char* dirname)
{
	// 发送当前dirname目录中的文件名到客户端
	// 1. 遍历dirname目录 -> 所有的文件名
#if 0
	// 打开目录
	DIR* dir = opendir(dirname);
	if (dir == NULL)
	{
		perror("opendir");
		return -1;
	}
	// 读目录
	struct dirent* ptr;
	while ((ptr = readdir(dir))!= NULL)
	{
		char* name = ptr->d_name;
	}
	closedir(dir);
#else
	char buf[4096];
	struct dirent **namelist;
	sprintf(buf, "<html><head><title>%s</title></head><body><table>", dirname);
	int num = scandir(dirname, &namelist, NULL, alphasort);
	for (int i = 0; i < num; ++i)
	{
		// 取出文件名
		char* name = namelist[i]->d_name;
		// 获取文件属性
		struct stat st;
		char subPath[1024];
		sprintf(subPath, "%s/%s", dirname, name);
		int ret = stat(subPath, &st);
		if (S_ISDIR(st.st_mode))
		{
			sprintf(buf + strlen(buf), 
				"<tr><td><a href=\"%s/\">%s/</a></td><td>%ld</td></tr>",
				name, name, (long)st.st_size);
		}
		else
		{
			sprintf(buf + strlen(buf), 
				"<tr><td><a href=\"%s\">%s</a></td><td>%ld</td></tr>",
				name, name, (long)st.st_size);
		}
		cout << buf << endl;
		// 发送数据
		send(cfd, buf, strlen(buf), 0);
		// 重置buf
		memset(buf, 0, sizeof(buf));
	}
	sprintf(buf, "</table></body></html>");
	send(cfd, buf, strlen(buf), 0);
	cout << buf << endl;

#endif
	// 2. 将得到的文件名放到table表格中
	/*
		<html>
			<head></head>
			<body>
				<table>
					<tr>
						<td></td>
						<td></td>
						<td></td>
						<td></td>
					</tr>
				</table>
			</body>
		</html>
	*/
	return 0;
}

int hexit(char c)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'f')
		return c - 'a' + 10;
	if (c >= 'A' && c <= 'F')
		return c - 'A' + 10;

	return 0;
}

// 解码
void decodeMsg(char *to, char *from)
{
	for (; *from != '\0'; ++to, ++from)
	{
		// isxdigit -> 判断字符是不是16进制格式
		// Linux%E5%86%85%E6%A0%B8.jpg
		if (from[0] == '%' && isxdigit(from[1]) && isxdigit(from[2]))
		{
			// 将16进制的数 -> 十进制 将这个数值赋值给了字符 int -> char
			// A1 == 161
			*to = hexit(from[1]) * 16 + hexit(from[2]);

			from += 2;
		}
		else
		{
			*to = *from;
		}

	}
	*to = '\0';
}

