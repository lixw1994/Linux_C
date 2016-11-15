#include <sys/stat.h>
#include <sys/uio.h>
#include <fcntl.h>
#include "tlpi_hdr.h"

int main(int argc, char const *argv[])
{
	int fd;
	struct iovec iov[3];
	struct stat myStruct;
	int x;
	#define STR_SIZE 100
	char str[STR_SIZE];
	ssize_t numRead, totrequired;

	if(argc != 2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s file\n", argv[0]);

	fd = open(argv[1], O_RDONLY);
	if(fd == -1)
		errExit("open");

	totrequired = 0;

	iov[0].iov_base = &myStruct;
	iov[0].iov_len = sizeof(struct stat);
	totrequired += iov[0].iov_len;
	// printf("%d\n", totrequired); 144

	iov[1].iov_base = &x;
	iov[1].iov_len = sizeof(x);
	totrequired += iov[1].iov_len;
	// printf("%d\n", totrequired); 148

	iov[2].iov_base = str;
	iov[2].iov_len = STR_SIZE;
	totrequired += iov[2].iov_len;
	// printf("%d\n", totrequired); 248

	numRead = readv(fd, iov, 3);
	if(numRead == -1)
		errExit("readv");
	if(numRead < totrequired)
		printf("Read fewer bytes than required: %ld, bytes read : %ld\n", 
			(long)totrequired, (long)numRead);
	printf("total bytes required: %ld; bytes read : %ld\n", 
			(long)totrequired, (long)numRead);
	exit(EXIT_SUCCESS);
	return 0;
}
















