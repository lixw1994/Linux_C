#include "../lib/tlpi_hdr.h"

int main(int argc, char const *argv[])
{
	char* argVec[10];
	char* envVec[] = {"GREEN=salut", "BYE=adieu", NULL};

	if(argc != 2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s pathname\n", argv[0]);

	argVec[0] = strrchr(argv[1], '/');
	if(argVec[0] != NULL)
		argVec[0]++;
	else
		argVec[0] = (char*)argv[1];

	argVec[1] = "hello world";
	argVec[2] = "goodbye";
	argVec[3] = NULL;
	// 最后都以NULL结尾

	execve(argv[1], argVec, envVec);
	// 如果执行到了这里就说明execve()执行出错
	errExit("execve");
}
