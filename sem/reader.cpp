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
    shmid = shmget(SHM_KEY, sizeof(int),IPC_CREAT | 0666);//获得共享内存
    if (shmid<0){
        printf("create shm error\n" );
            return -1;
    }
    void * shmptr;
    shmptr = shmat(shmid,NULL,0);//把自己连接到该地址空间
    if(shmptr == (void *)-1){
        printf("shmat error: %s\n",strerror(errno) );
        return -1;
    }
    int * data = (int *)shmptr;
    semid = semget(SHM_KEY,2,IPC_CREAT|0666);//创建并初始化2个信号量
    union semun semun1;
    semun1.val=0;
    semctl(semid,0,SETVAL,semun1);//将第一个信号量设置为0
    semun1.val=1;
    semctl(semid,1,SETVAL,semun1);//将第二个信号量设置为1
    struct sembuf sembuf1;
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
    return 0;
}
