#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/shm.h>
#include <errno.h>
#define SEM_KEY 4001
#define SHM_KEY 5678
union semun{
    int val;
};
int main(){
    int semid,shmid;
    shmid = shmget(SHM_KEY, sizeof(int),IPC_CREAT | 0666);//获得同一个共享内存
    if (shmid<0){
        printf("create shm error\n" );
            return -1;
    }
    void * shmptr;
    shmptr = shmat(shmid,NULL,0);//连接到与reader同一个共享内存
    if(shmptr == (void *)-1){
        printf("shmat error: %s\n",strerror(errno) );
        return -1;
    }
    int * data = (int *)shmptr;
    semid = semget(SHM_KEY,2,IPC_CREAT|0666);//接收与reader相同的信号量
  //  union semun semun1;
    struct sembuf sembuf1;
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
    return 0;
}
