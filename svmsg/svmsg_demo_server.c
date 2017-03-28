#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include "../lib/tlpi_hdr.h"

#define KEY_FILE "./README.md"

int main(int argc, char const *argv[])
{
	int msqid;
	key_t key;
	const int MQ_PERMS = S_IRUSR | S_IWUSR | S_IWGRP;

	// 检查是否其他服务进程已经运行 。。。 省略此段代码

	key = ftok(KEY_FILE, 1);
	if(key == -1)
		errExit("ftok");
	while((msqid = msgget(key, IPC_CREAT | IPC_EXCL | MQ_PERMS)) == -1)
	{
		if(errno == EEXIST)
		{
            msqid = msgget(key, 0);
            if(msqid == -1)
            	errExit("msgget failed to retrive old queue ID");
            if(msgctl(msqid, IPC_RMID, NULL) == -1)
            	errExit("msgget failed to delete old queue");
            printf("Removed old message queue (id=%d)\n", msqid);
		}
		else
		{
			errExit("msgget failed");
		}
	}

	exit(EXIT_SUCCESS);
}
