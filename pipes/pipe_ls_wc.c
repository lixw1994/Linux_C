#include <sys/wait.h>
#include "../lib/tlpi_hdr.h"

int main(int argc, char const *argv[])
{
	int pfd[2];

	if(pipe(pfd) == -1)
		errExit("pipe");

	switch(fork())
	{
	case -1:
		errExit("fork");
	case 0:
		// 子进程 ls 写入管道
		if(close(pfd[0]) == -1)
			errExit("close");

		if(pfd[1] != STDOUT_FILENO)
		{
			if(dup2(pfd[1], STDOUT_FILENO) == -1)
				errExit("dup2");
			if(close(pfd[1]) == -1)
				errExit("close");
		}

		execlp("ls", "ls", (char*)NULL);
		errExit("execlp");
	default:
		break;
	}

	switch(fork())
	{
	case -1:
		errExit("fork");
	case 0:
		// 子进程 wc 从管道读取
		if(close(pfd[1]) == -1)
			errExit("close");

		if(pfd[0] != STDIN_FILENO)
		{
			if(dup2(pfd[0], STDIN_FILENO) == -1)
				errExit("dup2");
			if(close(pfd[0]) == -1)
				errExit("close");
		}

		execlp("wc", "wc", "-l", (char*)NULL);
		errExit("execlp");
	default:
		break;
	}
	
	if(close(pfd[0]) == -1)
		errExit("close");
	if(close(pfd[1]) == -1)
		errExit("close");
	if(wait(NULL) == -1)
		errExit("wait");
	if(wait(NULL) == -1)
		errExit("wait");

	exit(EXIT_SUCCESS);
}
