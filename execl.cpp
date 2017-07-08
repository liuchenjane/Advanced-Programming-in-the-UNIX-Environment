#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main(){

    printf("Executing ls\n" );
    execl("/bin/ls","ls","-l",NULL);
//execl如果返回，说明调用失败
    perror("execl failed to run ls");
    exit(1);
}
