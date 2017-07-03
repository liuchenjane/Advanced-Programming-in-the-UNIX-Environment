#include <stdio.h>
#include <pthread.h>
void * function(void * arg){
    printf("thread id in pthread=%lu\n", pthread_self());
    pthread_exit((void *)1);
}

int main(){
    int i=10;
    pthread_t thread;
    int iRet = pthread_create(&thread, NULL, &function, &i);
    if(iRet){
        printf("pthread_create error, iRet=%d\n",iRet );
        return iRet;
    }
    printf("thread id in process=%lu\n",thread );
    void *retval;
    iRet=pthread_join(thread, &retval);
    if(iRet){
        printf("pthread_join error, iRet=%d\n",iRet );
        return iRet;
    }
    printf("retval=%ld\n",(long )retval);
}
