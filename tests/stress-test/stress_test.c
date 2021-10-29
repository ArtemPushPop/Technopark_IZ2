#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "data_path.h"



int MakeCommand(char *cmd, size_t cmd_len, char *path, char *letters){
    cmd[cmd_len] = '\0';
    strcat(cmd, " -f ");
    strcat(cmd, path);
    strcat(cmd, " -p ");
    strcat(cmd, letters);
    return 0;
}


int MakePath(char *path, const char* dir, const char *file_name){
    path[strlen(dir)] = '\0';
    strcat(path, dir);
    strcat(path, file_name);
    return 0;
}

int main(){
    char cmd_consistent[256];
    strcpy(cmd_consistent, "./consistent_test");
    size_t consistent_len = strlen(cmd_consistent);

    char cmd_parallel[256];
    strcpy(cmd_parallel, "./parallel_test");
    size_t parallel_len = strlen(cmd_parallel);

    char files_path[256];
    char file_name[] = "file1.txt";

    FILE *results[2][FILES_NUM];
    results[1][1] = 0;

    for (int i = 0; i < FILES_NUM; i++){
        file_name[4] = '1' + (char)i;
        MakePath(files_path, DATA_FILES_PATH, file_name);
        MakeCommand(cmd_consistent, consistent_len, files_path, "ab");
        if ((results[0][i] = popen(cmd_consistent, "r")) == NULL)
            exit(1);
        MakeCommand(cmd_parallel, parallel_len, files_path, "ab");
        if ((results[1][i] = popen(cmd_parallel, "r")) == NULL)
            exit(1);
    }

    size_t res1, res2;
    for (int i = 0; i < FILES_NUM; i++){
        fscanf(results[0][i], "%lu", &res1);
        pclose(results[0][i]);
        fscanf(results[1][i], "%lu", &res2);
        pclose(results[1][i]);
        if (res1 != res2)
            printf("RESULTS MISMATCH! FROM FILE: file%d.txt\n", i + 1);
        else
            printf("RESULTS MATCH! FROM FILE: file%d.txt\n", i + 1);
    }
    return 0;
}
