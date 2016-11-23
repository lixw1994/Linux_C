1. 定时器：定时器是进程规划自己在未来某一时刻接获通知的一种机制。
2. 间隔定时器(interval timer)：
    #include <sys/time.h>
    int setitimer(int which, const struct itimerval* new_value, 
        const struct itimerval* old_value);
    两个关键的结构体：struct itimerval{..., ...}; struct timeval{..., ...};
    int getitimer(int which, const struct itimerval* curr_value);
3. 简单的定时器接口：alarm()
    #include <unistd.h>
    unsigned int alarm(unsigned int seconds);
    注意：为了保证程序的可移植性，上述两个接口最好只用一个。
4. 为阻塞设置超时：
    1. 调用sigaction()为SIGALRM信号创建处理器函数，排除SA_RESTART标志以确保系统调用不会重新启动
    2. 调用alarm()或者setitimer()来创建一个定时器，同时设定希望系统调用阻塞的时间上限。
    3. 执行阻塞时系统调用。
    4. 系统调用成功返回后，再次调用alarm()或setitimer()以屏蔽定时器(防止系统调用在定时器到期之前完成)
    5. 检查调用失败时是否将errno置为EINTR（系统调用遭到中断）
5. 休眠一段时间
    低分辨率休眠：sleep();    高分辨率休眠：nanosleep();