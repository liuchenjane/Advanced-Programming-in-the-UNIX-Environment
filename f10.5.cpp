#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(){
    pid_t pid = fork();
    if (pid > 0){
        printf("in parent process, sleep for one miniute .. \n" );
        sleep(3);
        printf("after sleeping, and exit!\n" );
    }else if(pid == 0){
        printf("in child process, and exit\n" );
        exit(0);
    }
    return 0;
}
