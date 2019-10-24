#include <cstdio>
#include "server.h"
#include <stdlib.h>
#include <iostream>
#include <unistd.h>
using namespace std;

int main(int argc, char* argv[])
{
	// ./a.out port 资源根目录
	if (argc < 3)
	{
		cout << "实例: ./a.out 端口 资源根目录" << endl;
		exit(0);
	}
	// 端口转换
	unsigned short port = atoi(argv[1]);
	// 进程切换到指定的资源目录中
	chdir(argv[2]);

	int lfd = initListen(port);
	// 启动epoll
	epollRun(lfd);

    return 0;
}