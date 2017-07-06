## 文件IO函数<br>
对于内核：所有打开的文件都通过文件描述符引用<br>
- open()
打开或创建一个文件<br>
```c
#include <fcntl.h>
int open(const char *path, int aflag,.../* mode_t mode */);
/*path:打开或创建文件的名字；
* aflag:或多个常量，O_RDONLY,O_WRONLY,O_RDWR,O_CREAT
* O_CREAT:若此文件不存在则创建它，使用此项时，要用mode,指定新文件的访问权限
*/
```

- write()
向打开文件中写数据<br>
```c
#include <unistd.h>
ssize_t write(int fd, const void*buf, size_t nbytes);
//若成功，返回以写的字节数；若出错，返回-1；
//在一次写成功后，文件偏移量增加实际写的字节数
```
- read()
从打开的文件中读数据<br>
```c
#include <unistd.h>
ssize_t read(int fd,void *buf,size_t nbytes);
//如读成功，则返回读到的字节数。如到达文件的尾端，则返回0；如出错，返回-1
//读操作从文件的当前偏移量开始，在成功返回之前，偏移量将增加实际读到的字节数
```
- close()
关闭一个打开文件，当一个进程终止时，内核自动关闭它所有的打开文件。<br>
```c
#include <unistd.h>
int close(int fd);
```
- ftok()
