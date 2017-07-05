#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#define MAXFILE 65535
int main(){
    pid_t pc;
    int i,fd,len;
    char *buf="this ia a Dameon\n";
    len=strlen(buf);
    pc=fork();//第一步：创建子进程，并且父进程退出
    if(pc<0){
        printf("error fork\n" );
        exit(1);
    }else if(pc>0){
        exit(0);
    }
    setsid();//第二步：在子进程中创建新会话，让进程完全独立，不受原会话，原进程组，原终端控制。
    chdir("/");//改变当前目录为根目录
    umask(0);//重设文件掩码
    for(i=0;i<MAXFILE;i++)//关闭文件描述符
        close(i);
    while(1){
        if((fd=open("/tmp/dameon.log",O_CREAT|O_WRONLY|O_APPEND,0600))<0){
            perror("open");
            exit(1);
        }
        write(fd,buf,len+1);
        close(fd);
        sleep(10);
    }
    return 0;
}
