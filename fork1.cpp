#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main(){
    pid_t pid;
    pid = fork();
    if (pid < 0){
        perror("fail to fork");
        exit(-1);
    }
    else if(pid == 0){
        printf("sub-process, PID: %u, PPID: %u\n",getpid(),getppid());
        //getpid()获取当前进程的pid，getppid()获得父进程的pid
    }
    else{
        printf("Parent, PID: %u, Sub-process PID:%u\n",getpid(),pid );
            sleep(2);
    }
    return 0;
}
