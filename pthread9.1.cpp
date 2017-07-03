#include <stdio.h>
#include <pthread.h>
void * say_hello(void * args){
    /*线程的运行函数，必须为void* */
    printf("hello from thread\n" );
    pthread_exit((void *)1);
}
int main(){
    pthread_t tid;
    int iRet = pthread_create(&tid, NULL, say_hello, NULL);

    if (iRet){
        printf("pthread_create error: iRet=%d\n",iRet );
        return iRet;
    }
    void *retval;
    iRet=pthread_join(tid,&retval);
    if (iRet){
        printf("pthread_join error; iRet=%d\n",iRet );
        return iRet;
    }
    printf("retval=%ld\n",(long)retval );
    return 0;
}
/*线程创建函数：
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine) (void *), void *arg);
第一个参数：指向线程标识符的指针；第二个参数：设置线程属性；第三个参数：线程运行函数的起始地址；第四个参数：运行函数的参数。
返回值：如线程创建成功，返回0；否则返回出错编号

主线程调用，等待子线程结束
int pthread_join(pthread_t thread, void ** retval);
第一个参数：被等待的线程标识符；第二个参数：存储被等待进程的返回值

子线程调用，结束当前进程
void pthread_exit(void *treval);
*/
