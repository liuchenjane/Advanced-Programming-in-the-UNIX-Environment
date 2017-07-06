writer部分：<br>
```c
while(1){
        sembuf1.sem_num=1;//对第二个信号量操作
        sembuf1.sem_op=-1;//-1,reader中将其初始值设为1
        sembuf1.sem_flg=SEM_UNDO;
        semop(semid,&sembuf1,1);
        scanf("%d",data);//用户在终端输入
        sembuf1.sem_num=0;//对第一个信号量操作
        sembuf1.sem_op=1;//加1
        sembuf1.sem_flg=SEM_UNDO;
        semop(semid,&sembuf1,1);
    }
```  
reader部分：<br>
```c
while(1){
        sembuf1.sem_num=0;//下面操作的是第一个信号量
        sembuf1.sem_op=-1;//初始值为0,-1操作等待
        sembuf1.sem_flg=SEM_UNDO;
        semop(semid,&sembuf1,1);
        printf("the NUM:%d\n",*data );
        sembuf1.sem_num=1;//让writer再次就绪
        sembuf1.sem_op=1;
        sembuf1.sem_flg=SEM_UNDO;
        semop(semid,&sembuf1,1);
    }
```
reader和writer连接到同一个共享内存，并接收相同的信号量。<br>
两个信号量的初始化如下：<br>
```c
    semun1.val=0;
    semctl(semid,0,SETVAL,semun1);//将第一个信号量设置为0
    semun1.val=1;
    semctl(semid,1,SETVAL,semun1);//将第二个信号量设置为1
```
### reader部分的执行：<br>
第一个信号量的初始值为0,因此-1的话会等待，直至收到信号。这个信号是由writer部分给出的。<br>
### writer部分执行：<br>
当writer在写完之后，会对第一个信号量加一，这会解决reader的阻塞，reader会就绪读数。此时第一个信号量为0,没有reader部分的信号不会接着写。
### 再回到reader:<br>
reader部分在可以读完之后，重设第二个信号量为1，这可以让writer再次就绪。
