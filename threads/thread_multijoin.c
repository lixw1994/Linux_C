// 连接所有已终止的线程的主线程

#include <pthread.h>
#include "../lib/tlpi_hdr.h"

static pthread_cond_t threadDied = PTHREAD_COND_INITIALIZER;
static pthread_mutex_t threadMutex = PTHREAD_MUTEX_INITIALIZER;

static int totThreads = 0;
static int numLive = 0;

static int numUnjoined = 0;

enum tstate
{
	TS_ALIVE,
	TS_TERMINATED,
	TS_JOINED
};

static struct{
	pthread_t tid;
	enum tstate state;
	int sleepTime;
}*thread;

static void* threadFunc(void* arg)
{
	// int idx = (int)arg;
	int idx = *((int*)arg);
	printf("idx = %d\n", idx);
	int s;
	sleep(thread[idx].sleepTime);
	printf("Thread %d terminating\n", idx);

	s = pthread_mutex_lock(&threadMutex);
	if(s != 0)
		errExitEN(s, "pthread_mutex_lock");

	numUnjoined++;
	thread[idx].state = TS_TERMINATED;

	s = pthread_mutex_unlock(&threadMutex);
	if(s != 0)
		errExitEN(s, "pthread_mutex_unlock");
	s = pthread_cond_signal(&threadDied);
	if(s != 0)
		errExitEN(s, "pthread_cond_signal");

	return NULL;
}

int main(int argc, char const *argv[])
{
	int s, idx;

	if(argc < 2 || strcmp(argv[1], "--help") == 0)
		usageErr("%s nsecs...\n", argv[0]);

	thread = calloc(argc - 1, sizeof(*thread));
	if(thread == NULL)
		errExit("calloc");

	// 创建所有的线程
	for(idx = 0; idx < argc-1; idx++)
	{
		thread[idx].sleepTime = getInt(argv[idx+1], GN_NONNEG, NULL);
		thread[idx].state = TS_ALIVE;
		
		// s = pthread_create(&thread[idx].tid, NULL, threadFunc, (void*)idx);
		s = pthread_create(&thread[idx].tid, NULL, threadFunc, &idx);
		if(s != 0)
			errExitEN(s, "pthread_create");	
	}

	totThreads = argc - 1;
	numLive = totThreads;

	// 连接所有已经终止的线程
	while(numLive > 0)
	{
		s = pthread_mutex_lock(&threadMutex);
		if(s != 0)
			errExitEN(s, "pthread_mutex_lock");
		while(numUnjoined == 0)
		{
			s = pthread_cond_wait(&threadDied, &threadMutex);
			if(s != 0)
				errExitEN(s, "pthread_cond_wait");
		}

		for(idx = 0; idx < totThreads; idx++)
		{
			if(thread[idx].state == TS_TERMINATED)
			{
				s = pthread_join(thread[idx].tid, NULL);
				if(s != 0)
					errExitEN(s, "pthread_join");

				thread[idx].state = TS_JOINED;
				numLive--;
				numUnjoined--;

				printf("Repead thread %d (numLive=%d)\n", idx, numLive);
			}
		}
		s = pthread_mutex_unlock(&threadMutex);
		if(s != 0)
			errExitEN(s, "pthread_mutex_unlock");
	}

	exit(EXIT_SUCCESS);
}

