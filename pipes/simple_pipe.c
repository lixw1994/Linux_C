// 父进程向子进程传输数据

#include <sys/wait.h>
#include "../lib/tlpi_hdr.h"

#define BUF_SIZE 10

int main(int argc, char const *argv[])
{
	int pfd[2];
	char buf[BUF_SIZE];
	ssize_t numRead;

	if(argc != 2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s string \n", argv[0]);

	if(pipe(pfd) == -1)
		errExit("pipe");

	switch(fork())
	{
	case -1:
		errExit("fork");	
	case 0:
		if(close(pfd[1]) == -1)
			errExit("close");

		for(;;)
		{
			numRead = read(pfd[0], buf, BUF_SIZE);
			if(numRead == -1)
				errExit("read");
			if(numRead == 0)
			{
				write(STDOUT_FILENO, "\n", 1);
				break;
			}
			if(write(STDOUT_FILENO, buf, numRead) != numRead)
				fatal("child - partial/failed write");
		}
		
		if(close(pfd[0]) == -1)
			errExit("close");
		_exit(EXIT_SUCCESS);
	default:
		if(close(pfd[0]) == -1)
			errExit("close - parent");
		if(write(pfd[1], argv[1], strlen(argv[1])) != strlen(argv[1]))
			fatal("parent partial/failed write");
		if(close(pfd[1]) == -1)
			errExit("close -parent");
		wait(NULL);
		exit(EXIT_SUCCESS);
	}

}
