公用结构：<br>
```c
struct shared_use_st {
    int written;//可读或可写的标志，非0表示可读，0表示可写
    char text[TEXT_SZ];
};
```

## 1. consumer  
创建共享内存，并读取其中消息；<br>
在共享内存的结构体shared_use_st中的标志written，当有进程向它写入数据时,written=0,此时不可读，等待。<br>
当written=1时，没有进程在写，可以读取，读完后重新设置为0,可被其他进程写。
## 2. producer
向共享内存中写入数据；<br>
首先，检查written是否为0，如不为0，说明还有进程没有读完，等待；<br>
当written=0时，提示用户输入文本,写完后，将written=1.<br>

**以上操作不是原子的，不安全，要有进程同步进制**
