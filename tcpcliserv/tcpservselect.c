#include "../lib/tlpi_hdr.h"
#include <sys/select.h>
#include <time.h>
#include <sys/socket.h>

#define SERV_PORT 50001

int main(int argc, char const *argv[])
{
	int listenfd, sockfd, maxfd_value, maxi_key;
	struct sockaddr_in servaddr, cliaddr;
	int nReady, cli[FD_SETSIZE], connfd;
	fd_set allset, rset;
	int i, n;
	char buf[MAXLINE];

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd == -1)
		errExit("socket");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(SERV_PORT);
	if(bind(listenfd, (SA*)&servaddr, sizeof(servaddr)) == -1)
		errExit("bind");

	if(listen(listenfd, 500) == -1)
		errExit("listen");

	// 初始化select参数
	maxfd_value = listenfd;
	maxi_key = -1;
	for(i = 0; i < FD_SETSIZE; ++i)
		cli[i] = -1;
	FD_ZERO(&allset);
	FD_SET(listenfd, &allset);

	for(;;)
	{
		rset = allset;
		nReady = select(maxfd_value+1, &rset, NULL, NULL, NULL);
		if(nReady == -1)
		{
			errMsg("select");
			continue;
		}

		if(FD_ISSET(listenfd, &rset))
		{
			socklen_t clilen = sizeof(cliaddr);
			connfd = accept(listenfd, (SA*)&cliaddr, &clilen);
			if(connfd == -1)
			{
				errMsg("accept");
				continue;
			}
			// 加入监听队列
			for(i = 0; i < FD_SETSIZE; ++i)
			{
				if(cli[i] < 0)
				{
					cli[i] = connfd;
					FD_SET(connfd, &allset);
					if(connfd > maxfd_value)
						maxfd_value = connfd;
					if(i > maxi_key)
						maxi_key = i;

					break;
				}
			}
			if(i == FD_SETSIZE)
				errExit("too many fd");

			if(--nReady <= 0)
				continue;
		}

		// for(i = 0; i < FD_SETSIZE; ++i)
		for(i = 0; i < maxi_key; ++i)
		{
			if(cli[i] > 0)
			{
				if(FD_ISSET(cli[i], &rset))
				{
					sockfd = cli[i];
					if((n = read(sockfd, buf, MAXLINE)) == 0)
					{
						close(sockfd);
						FD_CLR(sockfd, &allset);
						// 少了一步还原数组的代码
						cli[i] = -1;
					}
					if(write(sockfd, buf, n)!= n)
						errMsg("write");
					if(--nReady <= 0)
						break;
				}
			}
		}

	}

	exit(EXIT_SUCCESS);
}
