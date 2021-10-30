#pragma once


#define MAX_SEND_SIZE 80
#define MSG_TYPE 1


struct my_msgbuf{
    long mtype;
    char mtext[MAX_SEND_SIZE];
};
