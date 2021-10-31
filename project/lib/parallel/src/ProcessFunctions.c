#include "MyMsg.h"
#include "Errors.h"
#include "CodingFeatures.h"


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/msg.h>
#include <signal.h>


void handler(int signum){
    if (signum == SIGKILL){
        exit(SIGNAL_KILL);
    }
}


int FindSymbolInMap(const char map[], size_t size, const char symbols[], size_t coding, int msgqid){
    signal(SIGKILL, handler);

    size_t number_finded = 0;
    size_t j;
    size_t sym_size = strlen(symbols);
    for (size_t i = 0; i * coding < size; i++) {
        j = 0;
        while ((j * coding < sym_size) && (!CompareWithCoding(map + coding * i, symbols + coding * j, coding)))
            j++;
        if (j * coding != sym_size)
            (number_finded)++;
    }

    struct my_msgbuf msg;
    msg.mtype = MSG_TYPE;
    sprintf(msg.mtext, "%zu", number_finded);
    if (msgsnd(msgqid, (struct msgbuf *) &msg, strlen(msg.mtext) + 1, 0) == -1){
        exit(ERROR_MESSAGE_Q);
    };
    exit(0);
}
