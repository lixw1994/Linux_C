/*
	getenv()函数可以能够从进程中检索单个值，如果不存在返回NULL；
	修改环境变量可以用 int putenv(char * string) (通用) or 
		int setenv(const char* name, const char* value, int overwrite) (from BSD)
	完全清除整个环境：environ = NULL or 
		int clearenv(void)
*/


#include "tlpi_hdr.h"

extern char** environ;

int main(int argc, char const *argv[])
{
	char ** ep;
	for(ep = environ; ep != NULL; ep++)
		puts(*ep);

	return 0;
}
