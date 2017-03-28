#include "../lib/tlpi_hdr.h"
#include <netinet/in.h>
#include <arpa/inet.h>
#include <time.h>

#ifndef MAX_LINE
#define MAX_LINE 100
#endif

#define SA struct sockaddr

int main(int argc, char const *argv[])
{
	int listenfd, connfd;
	struct sockaddr_in servaddr;
	char buf[MAX_LINE];
	time_t ticks;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd == -1)
		err_exit("socket");

	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(50002);

	if(bind(listenfd, (SA*)&servaddr, sizeof(servaddr)) == -1)
		errExit("bind");

	if(listen(listenfd, 10) == -1)
		errExit("listen");

	for(;;)
	{
		printf("listen starting\n");
		connfd = accept(listenfd, (SA*)NULL, NULL);
		if(connfd == -1)
			errExit("connfd");

		ticks = time(NULL);
		snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));
		if(write(connfd, buf, strlen(buf)) != strlen(buf))
			errMsg("write");

		if(close(connfd) == -1)
			errMsg("close");
	}

}
