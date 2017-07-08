#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(){

    printf("Executing ls\n" );
    execl("/bin/ls","ls","-l",NULL);

    perror("execl failed to run ls");
    exit(1);
}
