#include "../lib/tlpi_hdr.h"
#include "../time/curr_time.h"

int main(int argc, char const *argv[])
{
	int pfd[2];
	int j, dummy;
	if(argc < 2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s sleep-time...\n", argv[0]);

	setbuf(stdout, NULL);

	printf("%s Parent started\n", currTime("%T"));

	// 创建一个管道
	if(pipe(pfd) == -1)
		errExit("pipe");

	for(j = 1; j < argc; j++)
	{
		switch(fork())
		{
		case -1:
			errExit("fork");
		case 0:
			if(close(pfd[0]) == -1)		// 关闭子进程的读入端
				errExit("close");
			// 子进程做一些事情
			sleep(getInt(argv[j], GN_NONNEG, "sleep-time"));
			printf("%s Child %d (PID=%ld) closing pipe\n", 
				currTime("%T"), j, (long)getpid());
			if(close(pfd[1]) == -1)
				errExit("close");
			// 子进程可以继续做一些事情
			_exit(EXIT_SUCCESS);

		default:		// 父进程循环创建下一个子进程
			break;
		}
	}

	// 父进程
	if(close(pfd[1]) == -1)
		errExit("close");

	if(read(pfd[0], &dummy, 1) != 0)
		fatal("parent didn't get EOF");
	printf("%s parent ready to go \n", currTime("%T"));

	exit(EXIT_SUCCESS);
}
