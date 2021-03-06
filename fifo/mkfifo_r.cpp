#include <stdio.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#define P_FIFO "/tmp/p_fifo"

int main(){
    char cache[1000];
    int fd;
    memset(cache,0,sizeof(cache));
    if(access(P_FIFO,F_OK)==0){//若管道文件存在，则删掉
        execlp("rm","-f",P_FIFO,NULL);
        printf("access.\n" );
    }
    if(mkfifo(P_FIFO,0777)<0){//创建一个有名管道
        printf("ceatenamed pipe failed\n" );
    }
    fd=open(P_FIFO, O_RDONLY | O_NONBLOCK);//以非阻塞只读方式打开管道
    while(1){
        memset(cache,0,sizeof(cache));
        //读数据
        if((read(fd,cache,100))==0){
            printf("nodata:\n" );
        }else{
            printf("get data: %s\n",cache );
        }
        sleep(1);
    }
    close(fd);
    return 0;
}
