#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <signal.h>
#include <time.h>

#ifndef MAXLINE
#define MAXLINE 100
#endif

#ifndef SA 
#define SA struct sockaddr
#endif

#ifndef LISTENQ
#define LISTENQ 50
#endif
