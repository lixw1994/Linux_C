#define _BSD_SOURCE

#include <netdb.h>
#include "is_seqnum.h"

#define BACKLOG 50

int main(int argc, char const *argv[])
{
	uint32_t seqNum;
	char reqLenStr[INT_LEN];
	char seqNumStr[INT_LEN];
	struct sockaddr_storage claddr;
	int lfd, cfd, optval, reqLen;
	socklen_t addrlen;
	struct addrinfo hints;
	struct addrinfo *result, *rp;
#define ADDRSTRLEN (NI_MAXHOST + NI_MAXSERV + 10)
	char addrStr[ADDRSTRLEN];
	char host[NI_MAXHOST];
	char service[NI_MAXSERV];

	if(argc > 1 && strcmp(argv[1], "--help") == 0)
		usageErr("%s [init-seq-num]\n", argv[0]);

	seqNum = (argc > 1) ? getInt(argv[1], 0, "init-seq-num") : 0;

	if(signal(SIGPIPE, SIG_IGN) == SIG_ERR)
		errExit("signal");

	memset(&hints, 0, sizeof(struct addrinfo));
	hints.ai_canonname = NULL;
	hints.ai_next = NULL;
	hints.ai_addr = NULL;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_family = AF_UNSPEC;    // IPv4 or IPv6
	hints.ai_flags = AI_PASSIVE | AI_NUMERICSERV;

	if(getaddrinfo(NULL, PORT_NUM, &hints, &result) != 0)
		errExit("getaddrinfo");

	// 遍历返回的列表知道创建socket成功
	optval = 1;
	for(rp = result; rp != NULL; rp = rp->ai_next)
	{
		lfd = socket(rp->ai_family, rp->ai_socktype, rp->ai_protocol);
		if(lfd == -1)
			continue;

		if(setsockopt(lfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval)) == -1)
			errExit("setsockopt");

		if(bind(lfd, rp->ai_addr, rp->ai_addrlen) == 0)
			break;

		// 本次遍历没有找到可用
		if(close(lfd) == -1)
			errExit("close");
	}

	if(rp == NULL)
		fatal("Cound not bind socket to any address");

	if(listen(lfd, BACKLOG) == -1)
		errExit("listen");

	freeaddrinfo(result);

	// 处理客户端连接
	for(;;)
	{
		addrlen = sizeof(struct sockaddr_storage);
		cfd = accept(lfd, (struct sockaddr*)&claddr, &addrlen);
		if(cfd == -1)
		{
			errMsg("accept");
			continue;
		}

		if(getnameinfo((struct sockaddr*)&claddr, addrlen, 
			host, NI_MAXHOST, service, NI_MAXSERV, 0) == 0)
			snprintf(addrStr, ADDRSTRLEN, "(%s, %s)", host, service);
		else
			snprintf(addrStr, ADDRSTRLEN, "(?UNKNOWN?)");
		printf("Connectoin from %s\n", addrStr);

		// 读入客户端的请求，发回序列号
		if(readLine(cfd, reqLenStr, INT_LEN) <= 0)
		{
			close(cfd);
			continue;
		}

		reqLen = atoi(reqLenStr);
		if(reqLen <= 0)
		{
			close(cfd);
			continue;
		}

		snprintf(seqNumStr, INT_LEN, "%d\n", seqNum);
		if(write(cfd, &seqNumStr, strlen(seqNumStr)) != strlen(seqNumStr))
			fprintf(stderr, "Error on write!");
		seqNum += reqLen;

		if(close(cfd) == -1)
			errMsg("close");
	}

}
