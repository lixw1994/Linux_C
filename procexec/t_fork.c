#include "tlpi_hdr.h"

static int idata = 111;			// 初始化数据段

int main(int argc, char const *argv[])
{
	int istack = 222;			// 栈段
	pid_t childPid;

	switch(childPid = fork())
	{
	case -1:
		errExit("fork");
	case 0:
		idata *= 3;
		istack *= 3;
		break;
	default:
		sleep(3);
		break;
	}

	printf("PID=%ld %s idata=%d istack=%d\n", (long)getpid(), 
		(childPid==0)?"child":"parent", idata, istack);
	return 0;
}
