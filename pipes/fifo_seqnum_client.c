// 客户端细节：进程退出时清理管道的文件描述符
#include "fifo_seqnum.h"

static char clientFifo[CLIENT_FIFO_NAME_LEN];

static void removeFifo(void)
{
	unlink(clientFifo);
}

int main(int argc, char const *argv[])
{
	int serverFd, clientFd;
	request req;
	response resp;
	if(argc > 1 && strcmp(argv[1], "--help") == 0)
		usageErr("%s [seq-len...]\n", argv[0]);

	umask(0);
	snprintf(clientFifo, CLIENT_FIFO_NAME_LEN, CLIENT_FIFO_TEMPLATE, (long)getpid());
	if(mkfifo(clientFifo, S_IRUSR | S_IWUSR | S_IWGRP) == -1
		&& errno != EEXIST)
		errExit("nkfifo");
	// 服务端用户可能随时终止进程，及时清理资源。
	if(atexit(removeFifo) != 0)
		errExit("atexit");

	req.pid = getpid();
	req.seqLen = (argc > 1)?getInt(argv[1], GN_GT_0, "seq-len"):1;

	serverFd = open(SERVER_FIFO, O_WRONLY);
	if(serverFd == -1)
		errExit("open %s", SERVER_FIFO);

	if(write(serverFd, &req, sizeof(request)) != sizeof(request))
		fatal("Can't write to server");

	// 阻塞等待服务器发送的数据
	clientFd = open(clientFifo, O_RDONLY);
	if(clientFd == -1)
		errExit("open %s", clientFifo);

	if(read(clientFd, &resp, sizeof(response)) != sizeof(response))
		fatal("Can't read response from server");

	printf("%d\n", resp.seqNum);


	exit(EXIT_SUCCESS);
}
