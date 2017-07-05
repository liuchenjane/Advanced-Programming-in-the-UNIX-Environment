#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <sys/msg.h>
#define MAX_TEXT 512

struct msg_st {
    long int msg_type;
    char text[MAX_TEXT];
};
int main(){
    int running =1;
    int msgid=-1;
    struct msg_st data;
    char buffer[BUFSIZ];
    //建立消息队列
    msgid = msgget((key_t)1234, 0666|IPC_CREAT);
    if (msgid == -1){
        fprintf(stderr,"msgget failed with error: %d\n", errno);
        exit(EXIT_SUCCESS);
    }
    while(running){
        printf("Enter some text:" );
        fgets(buffer, BUFSIZ, stdin);
        data.msg_type=1;
        strcpy(data.text, buffer);
        //发送数据
        if(msgsnd(msgid,(void *)&data, MAX_TEXT,0)==-1){
            fprintf(stderr, "msgsnd failed\n");
                exit(EXIT_FAILURE);
        }

        if(strncmp(data.text, "end",3)==0){
            running=0;
        }
    }

    if(msgctl(msgid, IPC_RMID,0)==-1){
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }
    exit(EXIT_SUCCESS);
}
