# Advanced-Programming-in-the-UNIX-Environment
UNIX 环境下编程 <br>

## 事前准备
ubuntu 下默认是没有pthread库，安装命令：
```shell
sudo apt-get install glibc-doc
sudo apt-get install manpages-posix-dev
```

编译时需要链接静态库文件pthread<br>
`g++ xxx.cpp -o xxx -lpthread` <br>

## 1. 多线程
[见多线程.md](https://github.com/liuchenjane/Advanced-Programming-in-the-UNIX-Environment/blob/master/%E5%A4%9A%E7%BA%BF%E7%A8%8B.md)<br>
