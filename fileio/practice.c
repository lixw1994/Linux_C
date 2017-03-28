#include "../lib/tlpi_hdr.h"
#include <string.h>
#include <fcntl.h>

int main(int argc, char const *argv[])
{
	int fd;
	char buf[100];
	fd = open("temp", O_RDWR | O_APPEND);
	if(fd == -1)
		errExit("open");

	if(lseek(fd, 0, SEEK_SET) == -1)
		errExit("lseek");
	if(write(fd, "newnew\0ew", 9) != 9)
		errExit("write");

	if(lseek(fd, 0, SEEK_SET) == -1)
		errExit("lseek");
	if(read(fd, buf, 20) != 20)
		errExit("read");
	buf[20] = '\0';

	printf("read: %s", buf);
	return 0;
}
