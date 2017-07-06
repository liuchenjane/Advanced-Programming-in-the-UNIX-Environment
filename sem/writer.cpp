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
    shmid = shmget(SHM_KEY, sizeof(int),IPC_CREAT | 0666);
    if (shmid<0){
        printf("create shm error\n" );
            return -1;
    }
    void * shmptr;
    shmptr = shmat(shmid,NULL,0);
    if(shmptr == (void *)-1){
        printf("shmat error: %s\n",strerror(errno) );
        return -1;
    }
    int * data = (int *)shmptr;
    semid = semget(SHM_KEY,2,IPC_CREAT|0666);
  //  union semun semun1;
    struct sembuf sembuf1;
    while(1){
        sembuf1.sem_num=1;
        sembuf1.sem_op=-1;
        sembuf1.sem_flg=SEM_UNDO;
        semop(semid,&sembuf1,1);
        scanf("%d",data);
        sembuf1.sem_num=0;
        sembuf1.sem_op=1;
        sembuf1.sem_flg=SEM_UNDO;
        semop(semid,&sembuf1,1);
    }
    return 0;
}
