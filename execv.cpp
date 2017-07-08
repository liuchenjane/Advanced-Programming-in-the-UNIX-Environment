#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(){

    printf("Executing ls\n" );
    char *av[]={"ls","-l",NULL};
    execv("/bin/ls",av);
    perror("execl failed to run ls");
    exit(1);
}
