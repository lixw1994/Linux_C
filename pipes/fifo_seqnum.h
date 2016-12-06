#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "../lib/tlpi_hdr.h"

#define SERVER_FIFO "/tmp/seqnum_sv"

#define CLIENT_FIFO_TEMPLATE "/tmp/seqnum_cl.%ld"

#define CLIENT_FIFO_NAME_LEN (sizeof(CLIENT_FIFO_TEMPLATE) + 20)

struct request
{
	pid_t pid;    // 请求的客户端PID
	int seqLen;   // 请求的长度
};

struct response
{
	int seqNum;
};
