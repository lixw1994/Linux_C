
#include <pthread.h>
#include "../lib/tlpi_hdr.h"

static void* threadFunc(void* arg)
{
	char* s = (char*)arg;
	printf("%s", s);

	return (void*)strlen(s);
}

int main(int argc, char const *argv[])
{
	pthread_t t1;
	void* res;
	int s;

	s = pthread_create(&t1, NULL, threadFunc, "Hello thread\n");
	if(s != 0)
		errExitEN(s, "thread_create");

	printf("Message from main()\n");

	s = pthread_join(t1, &res);
	if(s != 0)
		errExitEN(s, "pthread_join");

	printf("Thread returned %ld\n", (long)res);

	return 0;
}
