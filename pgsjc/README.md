1. 进程组由一个或者多个共享同一进程组标识符(PGID)的进程组成。进程组ID是一个数字；一个进程组
    拥有一个进程组首进程，该进程是创建该组的进程，其进程ID为该进程组的ID。
2. 进程组的首进程无需是最后一个离开进程组的成员
3. 会话是一组进程组的集合。会话首进程是创建该会话的进程，其进程ID成为会话ID。一个会话的所有进程
    共享单个终端。控制终端会在会话首进程首次打开一个终端时被建立。
4. 在任一时刻，会话中其中一个进程组会成为终端的前台进程组，其他进程组会成为后台进程组。只有前台
    进程组中的进程才能从控制终端中读取输入。
5. 对于任务中的各个进程来讲，父、子进程都可以使用setpgid()来修改子进程的进程组ID。但是，
    由于父进程执行fork()之后父进程与子进程的调度顺序的无法确定的，因此无法依靠父进程在子进程
    执行exec()之前来改变子进程的进程组ID，同样也无法依靠子进程在父进程向其发送任意作业控制信号
    之前修改其进程ID。因此在编写shell控制程序时需要让父进程和子进程在fork()调用之后立即调用
    setpgid()来讲子进程ID设置为同样的值，并且父进程需要忽略所有的EACCES错误。
6. 进程的优先级(nice值)：使用fork()创建子进程会继承nice值并会在exec()调用中保持
7. 