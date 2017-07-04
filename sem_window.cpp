#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define CUSTOMER_NUM 10

/*
 *
 */
sem_t sem;
void * get_service(void *thread_id){
    int customer_id=*((int *)thread_id);
    if(sem_wait(&sem) == 0){
        usleep(100);
        printf("customer %d receive service ...\n",customer_id );
        sem_post(&sem);
    }
}
int main(){
    sem_init(&sem,0,2);
    pthread_t customers[CUSTOMER_NUM];
    int i, iRet;

    for( i=0; i< CUSTOMER_NUM; i++){
        int customer_id = i;
        iRet=pthread_create(&customers[i], NULL, get_service, &customer_id);
        if (iRet){
            perror("pthread_create");
            return iRet;
        }else{
            printf("customer %d arrived.\n", i);
        }
        usleep(10);
    }
    int j;
    for(j=0; j<CUSTOMER_NUM; j++){
        pthread_join(customers[j],NULL);
    }
    sem_destroy(&sem);
    return 0;
}
