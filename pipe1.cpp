#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INPUT 0
#define OUTPUT 1
int main(){
    int fd[2];
    pid_t pid;
    char buf[256];
    int returned_count;
    pipe(fd);
    pid=fork();
    if(pid<0){
        printf("Error in fork\n" );
            exit(1);
    }else if(pid==0){//子进程
        printf("int the child process...\n" );
        //子进程向父进程写数据，关闭管道的读端
            close(fd[INPUT]);
            write(fd[OUTPUT],"hello world",strlen("hello world"));
            exit(0);
    }else{//父进程
        printf("in the parent process...\n" );
        //父进程从子进程读数据，关闭管道的写端
        close(fd[OUTPUT]);
        returned_count=read(fd[INPUT], buf, sizeof(buf));
        printf("%d bytes of dtata received from child process: %s\n",returned_count, buf );
    }
    return 0;
}
