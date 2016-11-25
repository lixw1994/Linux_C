#include <unistd.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

int mySystem(const char* command)
{
	sigset_t blockingMask, origMask;
	struct sigaction saIgnore, saOrigQuit, saOrigInt, saDefault;
	pid_t childPid;
	int status, savedErrno;

	if(command == NULL)
		return mySystem(":") == 0;
	sigemptyset(&blockingMask);
	sigaddset(&blockingMask, SIGCHLD);
	sigprocmask(SIG_BLOCK, &blockingMask, &origMask);

	saIgnore.sa_handler = SIG_IGN;
	saIgnore.sa_flags = 0;
	sigemptyset(&saIgnore.sa_mask);
	sigaction(SIGINT, &saIgnore, &saOrigInt);
	sigaction(SIGQUIT, &saIgnore, &saOrigQuit);

	switch((childPid = fork()))
	{
	case -1:
		status = -1;
		break;
	case 0:
		saDefault.sa_handler = SIG_DFL;
		saDefault.sa_flags = 0;
		sigemptyset(&saDefault.sa_mask);

		if(saOrigInt.sa_handler != SIG_IGN)
			sigaction(SIGINT, &saDefault, NULL);
		if(saOrigQuit.sa_handler != SIG_IGN)
			sigaction(SIGQUIT, &saDefault, NULL);

		sigprocmask(SIG_SETMASK, &origMask, NULL);

		execl("/bin/sh", "sh", "c", command, (char*)NULL);
		_exit(127);

	default:
		while(waitpid(childPid, &status, 0) == -1)
		{
			if(errno != EINTR)
			{
				status = -1;
				break;
			}
		}
		break;
	}

	// 解除SIGCHLD，还原SIGINT和SIGQUIT

	savedErrno = errno;
	sigprocmask(SIG_SETMASK, &origMask, NULL);
	sigaction(SIGINT, &saOrigInt, NULL);
	sigaction(SIGQUIT, &saOrigQuit, NULL);
	errno = savedErrno;

	return status;
}
