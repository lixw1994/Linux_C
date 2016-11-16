// 利用信号来同步进程间动作--->以规避竞争条件

#include <signal.h>
#include "curr_time.h"
#include "tlpi_hdr.h"

#define SYNC_SIG SIGUSR1

static void handler(int sig)
{
	// 什么都不做
}

int main(int argc, char const *argv[])
{
	pid_t childPid;
	sigset_t blockMask, origMask, emptyMask;
	struct sigaction sa;

	setbuf(stdout, NULL);

	sigaddset(&blockMask, SYNC_SIG);
	if(sigprocmask(SIG_BLOCK, &blockMask, &origMask) == -1)
		errExit("sigprocmask");

	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sa.sa_handler = handler;
	if(sigaction(SYNC_SIG, &sa, NULL) == -1)
		errExit("sigaction");
	switch(childPid = fork())
	{
	case -1:
		errExit("fork");

	case 0:
		printf("[%s %ld] Child started - doing some work\n", 
			currTime("%T"), (long)getpid());
		sleep(2);
		printf("[%s %ld] Child about to signal parent\n", 
			currTime("%T"), (long)getpid());
		if(kill(getppid(), SYNC_SIG) == -1)
			errExit("kill");

		// 子进程可以做的事情...

		_exit(EXIT_SUCCESS);

	default:
		/// 父进程做的事情...

		printf("[%s %ld] Parent about to wait for signal\n", 
			currTime("%T"), (long)getpid());
		sigemptyset(&emptyMask);
		if(sigsuspend(&emptyMask) == -1 && errno != EINTR)
			errExit("sigsuspend");
		printf("[%s %ld] Parent got signal\n", 
			currTime("%T"), (long)getpid());
		if(sigprocmask(SIG_SETMASK, &origMask, NULL) == -1)
			errExit("sigprocmask");

		// 父进程继续做事情...
		exit(EXIT_SUCCESS);
	}
	return 0;
}















