#include <signal.h>
#include "tlpi_hdr.h"

static void sigHandler(int sig)
{
	static int count = 0;
	// printf和exit()函数是non-async-signal-safe functions

	if(sig == SIGINT){
		count++;
		printf("Caught SIGINT (%d)\n", count);
		return;
	}

	printf("Caught SIGQUIT - that's all forks!\n");
	exit(EXIT_SUCCESS);
}

int main(int argc, char const *argv[])
{
	if(signal(SIGINT, sigHandler) == SIG_ERR)
		errExit("signal");
	if(signal(SIGQUIT, sigHandler) == SIG_ERR)
		errExit("signal");
	for(;;)
	{
		pause();	// 阻塞知道一个信号被捕获
	}
	// return 0;
}
