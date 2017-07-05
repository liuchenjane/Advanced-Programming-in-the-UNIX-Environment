#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main(){
    pid_t pid,pr;
    pid=fork();
    if(pid<0)
        printf("Error occurder on forking.\n" );
    else if(pid==0){
        printf("Sub-process will sleep for 10 seconds.\n" );
        sleep(10);
        exit(0);
    }
    else if(pid>0){
        do{
            pr=waitpid(pid,NULL, WNOHANG);

            if(pr==0){
                printf("No child exited\n");
                sleep(1);
            }
        }while(pr==0);
        if(pr==pid)
            printf("successfully get child %d\n",pr );
        else {
            printf("some error occured\n" );
        }
    }
    return 0;
}

