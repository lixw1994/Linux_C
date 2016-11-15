// 为SIGINT信号安装一个处理器程序 /* SIGINT：2  终端中断 */

#include <signal.h>
#include "tlpi_hdr.h"


static void sigHandler(int sig)
{
	printf("Ouch\n");		// 这是不安全的
}

int main(int argc, char const *argv[])
{
	int j;
	if(signal(SIGINT, sigHandler) == SIG_ERR)
		errExit("signal");

	for(j = 0; ; j++)
	{
		printf("%d\n", j);
		sleep(3);
	}
	return 0;
}
