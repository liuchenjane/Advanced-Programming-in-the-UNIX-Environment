#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#define CUSTOMER_NUM 10

/*信号量模拟窗口服务
 *假设只有两个服务窗口，只能同时服务两个；
 *当有多个可用的服务窗口到达时，若窗口已满，就等待；
 *如果有多个可用的窗口，就接收服务。
 */
sem_t sem;//信号量定义为全局变量，方便多个线程共享
void * get_service(void *thread_id){
    //thread_id要立即保存，可能马上会被更改
    int customer_id=*((int *)thread_id);
    if(sem_wait(&sem) >= 0){//表示当前信号量大于0，可以为顾客服务,并－1
        usleep(100);
        printf("customer %d receive service ...\n",customer_id );
        sem_post(&sem);//服务完成后，信号量加1
    }
}
int main(){
    sem_init(&sem,0,2);
    pthread_t customers[CUSTOMER_NUM];
    int i, iRet;

    for( i=0; i< CUSTOMER_NUM; i++){//为每个顾客生成一个线程
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
    int j;//这里不能用i做循环变量，可能线程正在访问i
    for(j=0; j<CUSTOMER_NUM; j++){
        pthread_join(customers[j],NULL);
    }
    sem_destroy(&sem);
    return 0;
}
