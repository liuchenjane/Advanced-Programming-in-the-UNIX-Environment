#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(){
    pid_t pid;
    pid=fork();

    switch(pid){
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            execl("/bin/ls","ls","-l","--color",NULL);
            perror("execl failed");
            exit(1);
        default:
            wait();
            printf("ls complete\n");
            exit(0);
    }
}
