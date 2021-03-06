#include <sys/time.h>
#include <sys/select.h>
#include "../lib/tlpi_hdr.h"

static void usageError(const char* name)
{
	fprintf(stderr, "Usage: %s {timeout|-} fd-num[rw]...\n", name);
	fprintf(stderr, "    - means infinite timeout; \n");
	fprintf(stderr, "    r = minitor for read\n");
	fprintf(stderr, "    w = monitor for write\n");
	fprintf(stderr, "    e.g.: %s - 0rw 1w\n", name);
}

int main(int argc, char const *argv[])
{
	fd_set readfds, writefds;
	int ready, nfds, fd, numRead, j;
	struct timeval timeout;
	struct timeval* pto;
	char buf[20];

	if(argc < 2 || strcmp(argv[1], "--help") == 0)
		usageError(argv[0]);

	if(strcmp(argv[1], "-") == 0)
		pto = NULL;
	else
	{
		pto = &timeout;
		timeout.tv_sec = getLong(argv[1], 0, "timeout");
		timeout.tv_usec = 0;
	}

	nfds = 0;
	FD_ZERO(&readfds);
	FD_ZERO(&writefds);

	for(j = 2; j < argc; j++)
	{
		numRead = sscanf(argv[j], "%d%2[rw]", &fd, buf);
		if(numRead != 2)
			usageError(argv[0]);

		if(fd >= nfds)
			nfds = fd + 1;
		if(strchr(buf, 'r') != NULL)
			FD_SET(fd, &readfds);
		if(strchr(buf, 'w') != NULL)
			FD_SET(fd, &writefds);
	}

	ready = select(nfds, &readfds, &writefds, NULL, pto);
	if(ready == -1)
		errExit("select");

	printf("ready = %d\n", ready);
	for(fd = 0; fd < nfds; fd++)
		printf("%d: %s%s\n", fd, FD_ISSET(fd, &readfds) ? "r" : "", 
			FD_ISSET(fd, &writefds) ? "w" : "");

	if(pto != NULL)
		printf("timeout after select(): %ld.%03ld\n", 
			(long)timeout.tv_sec, (long)timeout.tv_usec / 10000);

	exit(EXIT_SUCCESS);
}
