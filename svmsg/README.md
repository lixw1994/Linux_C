1. 消息队列用来在进程之间传递消息， 消息队列和管道作用类似，但是有两个重大差别：第一
    消息队列是存在边界的；第二是每条消息存在包括一个type整形字段，并且可以通过类型选择
    消息而不需要以写入的顺序类读取消息。
2. 信号量允许进程同步他们的动作。
3. 共享内存是最快的IPC方法。
4. IPC key的生成方法；IPC_PRIVATE  ftok()函数
5. IPC关联的数据结构和权限问题。
6. IPC标识符和客户端服务器程序：如果服务器重启或者崩溃，新的服务器进程不清楚与IPC对象
    当前的状态相关的历史信息。此时，服务器一般丢弃所有既有的客户端，删除上一个服务器进程
    创建的IPC对象，创建IPC对象的新实例。