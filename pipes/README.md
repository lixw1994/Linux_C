1. 一个管道是一个字节流：
    当讲到管道是一个字节流时意味着在使用管道是是不存在消息或者消息边界的概念的。从管道中读取数据的
    进程可以读取任意大小的数据块，而不管写入进程写入管道的数据块的大小是什么。通过管道写入的数据是
    顺序的；在管道中无法通过lseek()来随机访问数据。
2. 从管道中读取数据：
    试图从一个当前为空的管道中读取数据将会被阻塞直到有至少一个字节被写入到管道为止。如果管道的写入端关闭了，那么从管道中读取数据的进程在读完管道中剩余数据后会看到文件结束。
3. 管道是单向的
4. 可以确保写入不超过PIPE_BUF字节的操作是原子的：
    如果多个进程同时写入一个管道，那么他们在同一时刻写入的数据量不超过PIPE_BUF字节，那么就可以确保写入的数据不会相互混合。
5. 管道的容量是有限的：
    管道其实是一个在内核内存中维护的缓冲器，这个缓冲器储存能力是有限的；一旦管道被填满，后续进程的写入操作将会被阻塞知道读者进程读取了一些数据。
6. 关闭未使用的管道文件描述符：(以下是原因)
    关闭未使用的文件描述符不仅仅是为了确保进程不会耗尽其文件描述符的限制，这对于管道的正确使用是非常重要的。
    从管道中读取数据的进程会关闭其持有的管道的写入描述符，这样当其他进程完成输出并关闭其写入描述符
    之后，读者就能看到文件结束。如果读者进程没有关闭写入端，那么在其他进程关闭了写入描述符之后，读者也不会看到文件结束，即使它读完了所有数据。相反，read()会阻塞等待数据，因为内核知道至少还有
    一个管道的写入描述符是打开的。
    写入进程关闭其持有的读取描述符是出于不同的原因。当一个进程试图向一个管道中写入数据但是没有任何进程拥有该管道的读取描述符时，内核回向写入进程发送一个SIGPIPE的信号。默认情况下，会杀死进程，
    但是进程可以捕获或者忽略该信号，这样会导致write()操作失败。收到SIGPIPE或者得到EPIPE错误对
    于表示出管道的状态是有用的，这就是关闭读者描述符的原因。
    只有当所有引用一个管道的文件描述符被关闭后才会销毁管道以及释放管道占用的资源。
7. 通过管道与shell命令进行通信：
    FILE* popen(const char* command, const char* mode);
    popen()函数创建了一个管道，然后创建了一个子进程来执行shell，而shell又创建了一个子进程来执
    行command字符串。
    int pclose(FILE* stream);
    一旦IO结束之后用pclose()函数关闭管道并等待子进程的shell终止不应该使用fclose(),它不等待子
    进程)












