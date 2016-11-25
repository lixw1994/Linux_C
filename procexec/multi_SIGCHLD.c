#include <signal.h>
#include <sys/wait.h>
#include "print_wait_status.h"
#include "../time/curr_time.h"
#include "../lib/tlpi_hdr.h"

static volatile int numLiveChildren = 0;

static void sigChildHandler(int sig)
{
	int status, savedErrno;
	pid_t childPid;
	savedErrno = errno;
	printf("%s handler: Caught SIGCHLD\n", currTime("%T"));
	while((childPid = waitpid(-1, &status, WNOHANG)) > 0)
	{
		printf("%s handler: Repead child %ld - ", 
			currTime("%T"), (long)getpid());
		printWaitStatus(NULL, status);
		numLiveChildren--;
	}
	if(childPid == -1 && errno != ECHILD)
		errMsg("waitpid");
	sleep(5);
	printf("%s handler: returning\n", currTime("%T"));

	errno = savedErrno;
}

int main(int argc, char const *argv[])
{
	int j, sigCnt;
	sigset_t blockMask, emptyMask;
	struct sigaction sa;

	if(argc < 2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s child-sleep-time...\n", argv[0]);

	setbuf(stdout, NULL);

	sigCnt = 0;
	numLiveChildren = argc - 1;

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = 0;
	sa.sa_handler = sigChildHandler;
	if(sigaction(SIGCHLD, &sa, NULL) == -1)
		errExit("sigaction");

	// 阻塞SIGCHLD信号防止它在父进程调用sigsuspend()之前传递。
	// 阻塞信号的操作
	sigemptyset(&blockMask);
	sigaddset(&blockMask, SIGCHLD);
	if(sigprocmask(SIG_SETMASK, &blockMask, NULL) == -1)
		errExit("sigprocmask");

	for(j = 1; j < argc; j++)
	{
		switch(fork())
		{
		case -1:
			errExit("fork");
		case 0:
			sleep(getInt(argv[j], GN_NONNEG, "child-sleep-time"));
			printf("%s Child %d (PID=%ld) exiting\n", currTime("%T"), 
				j, (long)getpid());
			_exit(EXIT_SUCCESS);
		default:
			break;
		}
	}

	// 循环之后父进程在这里执行
	sigemptyset(&emptyMask);
	while(numLiveChildren)
	{
		if(sigsuspend(&emptyMask) == -1 && errno != EINTR)
			errExit("sigsuspend");
		sigCnt++;
	}

	printf("%s All %d children have terminated; SIGCHLD was caught ""%d times\n", 
		currTime("%T"), argc - 1, sigCnt);

	exit(EXIT_SUCCESS);
}















