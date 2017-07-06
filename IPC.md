## 1.管道 <br>
- 数据能由一个进程流向另一个进程；<br>
- 管道由于父子进程或者兄弟进程之间的通信；  
函数原型：   
```c
#include <unistd.h>
int pipe(int fd[2]);
```
一个进程由pipe()创建管道后，再使用fork()建立一个子进程，通过管道实现父子进程间通信。   
管道两端任务固定：fd[0]为管道读端，fd[1]为管道写端。	 <br>
[eg. 管道实现父子进程间通信](https://github.com/liuchenjane/Advanced-Programming-in-the-UNIX-Environment/blob/master/pipe1.cpp)<br>
- 有名管道(FIFO)<br>
	- 可以使互不相关的两个进程实现彼此间通信；<br>
	- 管道可以通过路径名指出，并且在文件系统中可见；<br>
	- 严格遵循先进先出原则；<br>
FIFO提供路径名与之关联，以FIFO的文件形式存在于文件系统中；不相关的进程可通过FIFO交换数据。<br>
函数原型：<br>
```c
#include <sys/types.h>
#include <sys/stat.h>
int mkfifo(const char * pathname, mode_t mode);
//pathname是创建后的FIFO名字
```
[eg. FIFO通信](https://github.com/liuchenjane/Advanced-Programming-in-the-UNIX-Environment/tree/master/fifo)<br>
只要客户端向服务器发送的指令小于PIPE_BUF,客户端可以通过有名管道向服务器发送数据，客户端可以知道服务器传发数据的管道名。<br>
但是，服务器不能用同一个管道来和所有的客户通信。<br>
常用解决方法：使用客户的进程pid作为管道名，客户把自己的进程号告诉服务器，服务器得到数据后建立管道，客户端到以自己名字命名的管道读取数据。<br>

## 2. 消息队列
消息队列是一个在系统内核中用来保存消息的队列，以消息链表的形式出现。<br>
函数：<br>
```c
//(1)创建新消息队列或取得已存在消息队列
int msgget(key_t key, int msgflag);
//msgflag=IPC_CREAT,没有该队列，则创建一个新标识符，若已存在则返回原标识符；msgflag=IPC_EXCL,若没有队列，返回-1，已存在，返回0

//(2) 向队列读/写消息
ssize_t msgrcv(int msqid, void *msgp, size_t msgsz, long msgtyp, int msgflg);//从队列中取用消息
//msqid:消息队列标识码；msgp:指向消息缓冲区的指针；msgtyp:从消息队列内读取的消息形态；
int msgsnd(int msqid, const void* msgp, size_t msgsz, int msgflg);//将数据放到消息队列
//msgflg:队列没有数据情况下，所采取的行动

//(3)设置消息队列属性
int msgctl(int msgqid, int cmd, struct msqid_ds *buf);//对消息队列msgqid执行cmd操作
cmd=IPC_STAT:获取消息队列对应的msqid_ds数据结构，放到buf;
cmd=IPC_SET:设置消息队列属性，属性存储在buf中；
cmd=IPC_RMID:从内核中删除msqid标识的消息队列。
```
[eg. 消息队列通信](https://github.com/liuchenjane/Advanced-Programming-in-the-UNIX-Environment/tree/master/msg)<br>

## 3.共享内存<br>
不同进程之间共享的内存通常安排在同一段物理内存中，允许不相关的进程访问同一个逻辑内存。<br>
函数原型：<br>
```c
#include <sys/shm.h>
int shmget(key_t key, int size, int flag);//创建共享内存
//参数key:有效地为共享内存段命名；size:指定需要共享的内存容量；flag:权限标志

void *shmat(int shmid, void * addr, int flag);//进程调用shmat将其连接到自身地址空间
//shmid:shmget返回的共享存储标识符；函数返回值：进程数据段所连接的实际地址

int shmdt(const void *shmaddr);//将共享内存从当前进程分离
```
[eg.共享内存进行进程间通信](https://github.com/liuchenjane/Advanced-Programming-in-the-UNIX-Environment/tree/master/shm)<br>

优点：不要求进程关系，直接访问内存，效率快<br>
缺点：shm没有提供进程同步机制<br>

## 4. 信号量（SYSTEM V）

函数原型：<br>
```c
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int semget(key_t key, int nsems, int semflg);//创建和打开信号量
//一旦创建信号量，就不能更改信号量的个数。只要不删除该信号量，就可以重新调用该函数，返回以前创建的值。

struct sembuf{
	short sem_num;
	short sem_op;//p(等待)操作：-1;V(发送信号)操作：+1
	short sem_flag;//SEM_UNDO,使系统跟踪信号，并在进程没有释放该信号量而终止时，由系统释放信号量
};
int semop(int semid, struct sembuf *sops, unsigned nsops);//改变信号量值

int semctl(int semid, int semnum, int cmd,...);//直接控制信号量信息
```
[用信号量解决共享内存同步问题，实现进程间通信](https://github.com/liuchenjane/Advanced-Programming-in-the-UNIX-Environment/tree/master/sem)
