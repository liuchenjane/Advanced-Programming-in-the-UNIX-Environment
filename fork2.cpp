#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int global = 1;//全局变量，存储在data段
int main(){
    pid_t pid;
    int stack = 1;//局部变量，存储在栈区
    int *heap;
    heap = (int *)malloc(sizeof(int));//heap指向动态分配的内存区域，在堆区
    *heap=3;
    pid = fork();
    if(pid<0){
        perror("fail to fork");
        exit(-1);
    }
    else if(pid == 0){
        global++;
        stack++;
        (*heap)++;
        printf("In sub-process, global: %d, stack: %d, heap: %d\n",global,stack,*heap );
        exit(0);
    }else{
        sleep(2);//休眠2s，确保子进程执行完毕，再执行父进程
        printf("In parent-process, global: %d, stack: %d, heap: %d\n",global,stack,*heap );
    }
    return 0;
}
