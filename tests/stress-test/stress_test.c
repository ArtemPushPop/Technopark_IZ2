#include "data_path.h"
#include "TimeItExecl.h"
#include "ExeclArgsCreater.h"


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>


int main() {
    char command[2][256];
    size_t command_len[2];
    strcpy(command[0], "./consistent_test");
    command_len[0] = strlen(command[0]);
    strcpy(command[1], "./parallel_test");
    command_len[1] = strlen(command[1]);

    char files_path[256];
    char file_name[] = "file1.txt";

    char results[256];
    size_t s_results[2][3];

    for (int i = 0; i < FILES_NUM; i++) {
        for (int j = 0; j < 2; j++) {
            file_name[4] = '1' + (char) i;
            MakePath(files_path, DATA_FILES_PATH, file_name);
            MakeCommand(command[j], command_len[j], files_path, "ab");
            TimeItExecl(command[j], results);
//            sscanf(results, "%lu %lu", s_results[j] + 0, s_results[j] + 1, s_results[j] + 2);
            sscanf(results, "%lu %lu", s_results[j] + 0, s_results[j] + 1);
        }
        if (s_results[0][0] != s_results[1][0])
            printf("RESULTS MISMATCH! FROM FILE: file%d.txt\n", i + 1);
        else
            printf("RESULTS MATCH! FROM FILE: file%d.txt\n", i + 1);
//        printf("TIME EXECUTED CONSISTENT FILE (file%d.txt): sec - %lu, microsec - %lu \n", i + 1, s_results[0][1], s_results[0][2]);
//        printf("TIME EXECUTED PARALLEL FILE (file%d.txt): sec - %lu, microsec - %lu \n", i + 1, s_results[1][1], s_results[1][2]);
        printf("TIME EXECUTED CONSISTENT FILE (file%d.txt): tacts - %lu \n", i + 1, s_results[0][1]);
        printf("TIME EXECUTED PARALLEL FILE (file%d.txt): tacts - %lu\n", i + 1, s_results[1][1]);
        printf("\n");
    }

    return 0;

//    size_t res1, res2;
//    for (int i = 0; i < FILES_NUM; i++) {
//        fscanf(results[0][i], "%lu", &res1);
//        pclose(results[0][i]);
//        fscanf(results[1][i], "%lu", &res2);
//        pclose(results[1][i]);
//        if (res1 != res2)
//            printf("RESULTS MISMATCH! FROM FILE: file%d.txt\n", i + 1);
//        else
//            printf("RESULTS MATCH! FROM FILE: file%d.txt\n", i + 1);
//    }
//    return 0;
}
