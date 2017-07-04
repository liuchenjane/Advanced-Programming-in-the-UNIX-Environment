#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>
#include <iostream>
using namespace std;

pthread_cond_t taxiCond=PTHREAD_COND_INITIALIZER;
pthread_mutex_t taxiMutex = PTHREAD_MUTEX_INITIALIZER;
int travelerCount=0;
void * traveler_arrive(void *name){
    cout<<"Traveler: "<<(char *)name<<" needs a taxi now!"<<endl;
    pthread_mutex_lock(&taxiMutex);
    travelerCount++;
    pthread_cond_wait(&taxiCond,&taxiMutex);
    pthread_mutex_unlock(&taxiMutex);
    cout<<"Traveler: "<<(char *)name<<" now got a taxi!"<<endl;
    pthread_exit((void*)0);
}

void *taxi_arrive(void * name){
    cout<<"taxi: "<<(char*)name<<" arrives."<<endl;
    while(1){
        pthread_mutex_lock(&taxiMutex);
        if(travelerCount>0){//只有当等待乘客数大于0时，才触发条件变量
            pthread_cond_signal(&taxiCond);
            pthread_mutex_unlock(&taxiMutex);
            break;
        }
        pthread_mutex_unlock(&taxiMutex);
    }
    pthread_exit((void*)0);
}

int main(){
    pthread_t tids[3];
    int iRet = pthread_create(&tids[0],NULL,taxi_arrive,(void*)(" Jack "));
    if(iRet){
        printf("pthread_create error: iRet=%d\n",iRet );
        return iRet;
    }
    printf("Time passing by.\n" );
    sleep(1);
        iRet = pthread_create(&tids[1],NULL,traveler_arrive,(void*)(" Susan "));
    if(iRet){
        printf("pthread_create error: iRet=%d\n",iRet );
        return iRet;
    }
    printf("Time passing by.\n" );
    sleep(1);
        iRet = pthread_create(&tids[2],NULL,taxi_arrive,(void*)(" Mike "));
    if(iRet){
        printf("pthread_create error: iRet=%d\n",iRet );
        return iRet;
    }
    printf("Time passing by.\n" );
    sleep(1);
    void *retval;
    for(int i=0;i<3;i++){
        iRet=pthread_join(tids[i],&retval);
        if (iRet){
            printf("pthread_join error: iRet=%d\n",iRet );
            return iRet;
        }
        printf("retval=%ld\n",(long)retval );
    }
    return 0;
}
