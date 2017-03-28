#include "../lib/tlpi_hdr.h"
#include <netinet/in.h>
#include <arpa/inet.h>

#ifndef MAX_LINE
#define MAX_LINE 100
#endif

int main(int argc, char const *argv[])
{
	int sockfd, n;
	char recvline[MAX_LINE + 1];
	struct sockaddr_in servaddr;

	if(argc != 2)
		usageErr("%s usage: a.out <IPAddress>", argv[0]);

	if((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
		errExit("socket");
	memset(&servaddr, 0, sizeof(struct sockaddr_in));
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(50002);		// 端口

	if(inet_pton(AF_INET, argv[1], &servaddr.sin_addr) <= 0)
		errExit("inet_pton");

	if(connect(sockfd, (struct sockaddr*)&servaddr, 
		sizeof(servaddr)) < 0)
		errExit("connect");

	while((n = read(sockfd, recvline, MAX_LINE)) > 0)
	{
		recvline[n] = 0;
		if(fputs(recvline, stdout) == EOF)
			errExit("fputs");
	}

	if(n < 0)
		errExit("read");

	exit(EXIT_SUCCESS);


	return 0;
}