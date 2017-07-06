# Programming-in-the-UNIX-Environment
UNIX 环境下编程 <br>

---
最近在看《后台开发核心技术与应用实践》by徐晓鑫中关于多线程、进程和IPC的章节，脉络很清晰，适合初学者慢慢入手，结合其他经典UNIX书籍再深入。<br>

---

## 事前准备
ubuntu 下默认是没有pthread库，安装命令：
```shell
sudo apt-get install glibc-doc
sudo apt-get install manpages-posix-dev
```

编译时需要链接静态库文件pthread<br>
`g++ xxx.cpp -o xxx -lpthread` <br>

[文件IO等其他](https://github.com/liuchenjane/Programming-in-the-UNIX-Environment/blob/master/prepare.md)<br>
## 1. 多线程
[更多见多线程.md](https://github.com/liuchenjane/Advanced-Programming-in-the-UNIX-Environment/blob/master/%E5%A4%9A%E7%BA%BF%E7%A8%8B.md)<br>

- 多线程创建与结束<br>
	- 向线程运行函数传入类的静态成员函数<br>
	- 向线程运行函数传入单个参数<br>
	- 向线程运行函数传入多个参数组成结构体<br>
 - 线程属性<br>
 - 多线程同步<br>
	- 互斥锁
 	- 条件变量+互斥锁
	- 读写锁
	- 信号量
 
 ## 2. 进程
 [更多见进程.md](https://github.com/liuchenjane/Advanced-Programming-in-the-UNIX-Environment/blob/master/进程.md)<br>
 - 进程的创建与结束<br>
 	- fork()<br>
	- exit()<br>
- 僵尸进程<br>
	- wait()<br>
	- waitpid()<br>
- 守护进程<br>

## 3. 进程间通信IPC
常用的进程间通信方法：**管道、消息队列、共享内存、信号量、套接字**<br>
套接字用于不同机器间的网络通信，其他用于同一机器上的进程间通信。<br>
[更多见IPC.md](https://github.com/liuchenjane/Advanced-Programming-in-the-UNIX-Environment/blob/master/IPC.md)<br>
- 管道
- 消息队列
- 共享内存
- 信号量
- [套接字](https://github.com/liuchenjane/tcp_ip) 

