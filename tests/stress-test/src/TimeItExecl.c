#include "TimeItExecl.h"


#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>



char * TimeItExecl(const char * command, char result[]){
//    struct timeval begin, end;
//    gettimeofday(&begin, 0);
    clock_t begin = clock();
    FILE *pipe;
    if ((pipe = popen(command, "r")) == NULL)
        exit(1);

    size_t buf_size = 256;
    char buf[buf_size];
    fgets(buf, buf_size, pipe);

//    gettimeofday(&end, 0);
//    size_t seconds = end.tv_sec - begin.tv_sec;
//    size_t microseconds = end.tv_usec - begin.tv_usec;
    clock_t end = clock();

    sprintf(result, "%s %lu", buf, end - begin);

    pclose(pipe);

    return result;
}
