#include <sys/wait.h>
#include "print_wait_status.h"
#include "../lib/tlpi_hdr.h"

int main(int argc, char const *argv[])
{
	pid_t childPid;
	int status;

	if(argc < 1 || strcmp(argv[1], "--help") == 0)
		usageErr("%s [exit-status]\n", argv[0]);

	switch(childPid = fork())
	{
	case -1:
		errExit("fork");
	case 0:
		printf("Child started with PID=%ld\n", (long)getpid());
		if(argc > 1)
			exit(getInt(argv[1], 0, "exit-status"));
		else
			for(;;)
				pause();
		exit(EXIT_FAILURE);
	default:
		for(;;)
		{
			childPid = waitpid(-1, &status, WUNTRACED
		#ifdef WCONTINUED
				| WCONTINUED
		#endif
			);	// 返回终止信息和由于信号导致的停止信息
			if(childPid == -1)
				errExit("waitpid");

			printf("waitpid() returned: PID=%ld, status=0x%04x (%d,%d)\n", 
				(long)childPid, 
				(unsigned int)status, status >> 8, status & 0xff);
			printWaitStatus(NULL, status);

			if(WIFEXITED(status) || WIFSIGNALED(status))
				exit(EXIT_SUCCESS);

		}
	}
	return 0;
}

