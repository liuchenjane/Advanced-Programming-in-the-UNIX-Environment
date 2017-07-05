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
    }else if(pid==0){
        printf("int the child process...\n" );
            close(fd[INPUT]);
            write(fd[OUTPUT],"hello world",strlen("hello world"));
            exit(0);
    }else{
        printf("in the parent process...\n" );
        close(fd[OUTPUT]);
        returned_count=read(fd[INPUT], buf, sizeof(buf));
        printf("%d bytes of dtata received from child process: %s\n",returned_count, buf );
    }
    return 0;
}
