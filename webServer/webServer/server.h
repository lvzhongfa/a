// 防止头文件多重包含
#pragma once

// 初始化监听的套接字
int initListen(unsigned short port);
// 启动epoll模型
int epollRun(int lfd);
// 接受客户端连接
int acceptConn(int lfd, int epfd);
// 通信-> 接收客户端的请求数据
int recvHttpRequest(int cfd, int epfd);
// 断开连接
int disconnect(int cfd, int epfd);
// 解析请求行
int parseRequestLine(int cfd, const char* reqLine);
// 发送响应的数据头
int sendRespondHead(int cfd, int status, const char* descr, const char* type, int len);
// 发送文件给客户端
int sendFile(int cfd, const char* filename);
// 根据文件的后缀获取文件的Content-type
const char *getFileType(const char *name);
// 发送目录到客户端 -> html格式
int sendDir(int cfd, const char* dirname);
// 字符->整形
int hexit(char c);
// 解码
void decodeMsg(char *to, char *from);

