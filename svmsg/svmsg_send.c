#include "../lib/tlpi_hdr.h"
#include <sys/types.h>
#include <sys/msg.h>

#define MAX_MTEXT 1024

struct mbuf
{
	long mtype;
	char mtext[MAX_MTEXT];
};

static void usageError(const char* progName, const char* msg)
{
	if(msg != NULL)
		fprintf(stderr, "%s", msg);
	fprintf(stderr, "Usage: %s [-n] msqid msg-type [msg-text]\n", progName);
	fprintf(stderr, "    -n    Use IPC_NOWAIT flag\n");
	exit(EXIT_FAILURE);
}

int main(int argc, char const *argv[])
{
	int msqid, flags, msglen;
	struct mbuf msg;
	int opt;

	flags = 0;
	while((opt = getopt(argc, argv, "n")) != -1)
	{
		if(opt == 'n')
			flags |= IPC_NOWAIT;
		else
			usageError(argv[0], NULL);
	}

	if(argc < optind + 2 || argc > optind + 3)
		usageError(argv[0], "Wrong numer of arguments\n");

	msqid = getInt(argv[optind], 0, "msqid");
	msg.mtype = getInt(argv[optind+1], 0, "msg-type");

	if(argc > optind + 2)
	{
		msglen = strlen(argv[optind+2]) + 1;
		if(msglen > MAX_MTEXT)
			cmdLineErr("msg-text too long");

		memcpy(msg.mtext, argv[optind+2], msglen);
	}
	else
	{
		msglen = 0;
	}

	if(msgsnd(msqid, &msg, msglen, flags) == -1)
		errExit("msgsnd");
	
	exit(EXIT_SUCCESS);
	return 0;
}
