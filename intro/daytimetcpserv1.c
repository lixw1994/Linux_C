#include "../lib/tlpi_hdr.h"
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>

#define SA struct sockaddr

#ifndef MAXLINE
#define MAXLINE 100
#endif

int main(int argc, char const *argv[])
{
	int listenfd, connfd;
	socklen_t len;
	struct sockaddr_in servaddr, cliaddr;
	char buf[MAXLINE];
	time_t ticks;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd == -1)
		errExit("socket");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(13);

	if(bind(listenfd, (SA*)&servaddr, sizeof(servaddr)) == -1)
		errExit("bind");

	if(listen(listenfd, 100) == -1)
		errExit("listen");

	for(;;)
	{
		len = sizeof(cliaddr);
		connfd = accept(listenfd, (SA*)&cliaddr, &len);
		if(connfd == -1)
		{
			errMsg("accept");
			continue;
		}

		printf("connection from %s, port %d\n", 
			inet_ntop(AF_INET, &cliaddr, buf, sizeof(buf)), 
			ntohs(cliaddr.sin_port));

		ticks = time(NULL);
		snprintf(buf, sizeof(buf), "%.24s\r\n", ctime(&ticks));

		if(write(connfd, buf, strlen(buf)) != strlen(buf))
			errMsg("write");
		if(close(connfd) == -1)
			errMsg("close");

	}

	return 0;
}
