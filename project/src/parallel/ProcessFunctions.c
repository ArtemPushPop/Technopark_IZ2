#include "MyMsg.h"


#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/msg.h>



int FindSymbolInMap(const char map[], size_t size, const char symbols[], size_t coding, int msgqid){
    size_t sym_size = strlen(symbols);
    size_t number_finded = 0;
    if (coding == 1) {
        for (size_t i = 0; i < size; i++)
            for (size_t j = 0; j < sym_size; j++) {
                if (map[i] == symbols[j])
                    number_finded++;
            }
    }
    else
        for (size_t i = 0; i < size / coding; i++)
            for (size_t j = 0; j < sym_size / coding; j++) {
                int equal = 1;
                for (size_t z = 0; z < coding; z++){
                    if (map[i * coding + z] != symbols[j * coding + z])
                        equal = 0;
                }
                if (equal)
                    number_finded++;
            }

    struct my_msgbuf msg;
    msg.mtype = MSG_TYPE;
    sprintf(msg.mtext, "%zu", number_finded);
    if (msgsnd(msgqid, (struct msgbuf *) &msg, strlen(msg.mtext) + 1, 0) == -1){
        exit(-1);
    };
    exit(0);
}
