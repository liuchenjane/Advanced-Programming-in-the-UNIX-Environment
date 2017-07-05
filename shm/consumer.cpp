#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/shm.h>
#include "shm_com.h"
int main(){
    int shmid;
    srand((unsigned int)getpid());
    shmid = shmget((key_t)1234,sizeof(struct shared_use_st),0666| IPC_CREAT);//创建共享内存
    if(shmid == -1){
        fprintf(stderr, "shmget failed.\n");
            exit(EXIT_FAILURE);
    }
    void *shared_memory = (void*)0;
    shared_memory = shmat(shmid,(void *)0,0);//将共享内存映射到进程的地址空间
    if(shared_memory==(void *)-1){
        fprintf(stderr, "shmat failed.\n");
        exit(EXIT_FAILURE);
    }
    printf("Memory attached at %X\n",(long)shared_memory);
    struct shared_use_st *shared_stuff;
    shared_stuff = (struct shared_use_st*)shared_memory;//shared_memory分配给shared_stuff
    shared_stuff->written=0;
    int running = 1;
    while(running){
        if (shared_stuff->written){
            printf("You wrote: %s\n",shared_stuff->text);
            sleep(rand()%4);//为了让生产者等待
            shared_stuff->written=0;
            if(strncmp(shared_stuff->text, "end",3)==0){
                running=0;
            }   
        }
    }
    if(shmdt(shared_memory)==-1){//共享内存被分离
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    if (shmctl(shmid, IPC_RMID, 0)==-1){//删除
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);

    }
    exit(EXIT_SUCCESS);
}
