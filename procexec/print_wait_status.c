#define _GNU_SOURCE
#include <sys/wait.h>
#include <string.h>
#include "../lib/tlpi_hdr.h"
#include "print_wait_status.h"

void printWaitStatus(const char* msg, int status)
{
	if(msg != NULL)
		printf("%s", msg);
	if(WIFEXITED(status))
	{
		printf("child exited, status=%d\n", WEXITSTATUS(status));
	}
	else if(WIFSIGNALED(status))
	{
		printf("clild killed by signal %d(%s)", 
			WTERMSIG(status), (char*)strsignal(WTERMSIG(status)));
	#ifdef WCOREDUMP
		if(WCOREDUMP(status))
			printf("core dumped");
	#endif
		printf("\n");
	}
	else if(WIFSTOPPED(status))
	{
		printf("child stopped by signal %d(%s)\n", 
			WSTOPSIG(status), strsignal(WSTOPSIG(status)));

	#ifdef WIFCONTINUED
	}
	else if(WIFCONTINUED(status))
	{
		printf("child continued");
	#endif

	}
	else  // 不应该出现的东西
	{
        printf("what happened to this child?(status=%x)\n", 
        	(unsigned int)status);
	}

}











