// 服务端的细节：for循环不中断；FIFO打开一个额外的文件描述符，使得read保持阻塞；忽略SIGPIPE信号
#include <signal.h>
#include "fifo_seqnum.h"

int main(int argc, char const *argv[])
{
	int serverFd, dummyFd, clientFd;
	char clientFifo[CLIENT_FIFO_NAME_LEN];
	request req;
	response resp;
	int seqNum = 0;

	umask(0);
	if(mkfifo(SERVER_FIFO, S_IRUSR | S_IWUSR | S_IWGRP) == -1 && errno != EEXIST)
		errExit("mkfifo %s", SERVER_FIFO);
	serverFd = open(SERVER_FIFO, O_RDONLY);
	if(serverFd == -1)
		errExit("open %s", SERVER_FIFO);

	// 在服务端进程打开写端描述符，保证不会看到EOF
	dummyFd = open(SERVER_FIFO, O_WRONLY);
	if(dummyFd == -1)
		errExit("open %s", SERVER_FIFO);

	if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		errExit("signal");


	for(;;)
	{
		if(read(serverFd, &req, sizeof(request)) != sizeof(request))
		{
			fprintf(stderr, "Error reading request;discarding\n");
			continue;
		}
		
		snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, 
			CLIENT_FIFO_TEMPLATE, (long)req.pid);

		// 先前客户端请求时创建好的
		clientFd = open(clientFifo, O_WRONLY);
		if(clientFd == -1)
		{
			errMsg("open %s", clientFifo);
			continue;
		}

		// 发送回应内容
		resp.seqNum = seqNum;
		if(write(clientFd, &resp, sizeof(response)) != sizeof(response))
			fprintf(stderr, "Error writing to FIFO %s\n", clientFifo);
		if(close(clientFd) == -1)
			errMsg("close");

		seqNum += req.seqLen;
	}

}
