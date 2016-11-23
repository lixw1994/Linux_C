#include "../lib/tlpi_hdr.h"

int main(int argc, char const *argv[])
{
	printf("Hello world\n");
	write(STDOUT_FILENO, "Ciao\n", 5);

	if(fork() == -1)
		errExit("fork");


	exit(EXIT_SUCCESS);
}

// 这个程序在输出时如果直接运行./fork_stdio_buf 会正常输出
// 但是如果重定向 ./fork_stdio_buf > temp 会输出 Ciao Hello world Hello world
// 有两处需要解释：
// 1. 为什么会输出两个hello world? --> Stdio的缓冲区实在进程的用户空间维护的，在调用fork()时，
//    并没有刷新stdio的缓冲区，使得父进程的数据向子进程拷贝了一份；至于为什么终端输出没有这种情况，
// 	  因为终端默认是行缓冲，而重定向默认是块缓冲。
// 2. 为什么Ciao在前输出？ --> 因为在fork()之前，write()已经将数据传入的内核缓冲中，而printf会在
//    exit()调用之后刷新缓冲区。
