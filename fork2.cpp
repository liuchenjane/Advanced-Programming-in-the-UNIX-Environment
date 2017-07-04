#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int global = 1;
int main(){
    pid_t pid;
    int stack = 1;
    int *heap;
    heap = (int *)malloc(sizeof(int));
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
        sleep(2);
        printf("In parent-process, global: %d, stack: %d, heap: %d\n",global,stack,*heap );
    }
    return 0;
}
