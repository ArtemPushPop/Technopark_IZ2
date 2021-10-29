#include "main.h"
#include "CountSymbols.h"

#include <stdio.h>
#include <getopt.h>


int main(int argc, char *argv[]){
    //обработка опций
    int opt;
    char *file_name = DATA_FILE;
    char *pattern = "ab";
    char *opts = "f:p:";
    while ((opt = getopt(argc, argv, opts)) != -1){
        switch (opt) {
            case 'f' : file_name = optarg; break;
            case 'p' : pattern = optarg; break;
            default: break;
        }
    }

    size_t num_of_patterns = 0;
    FindNumSymbols(&num_of_patterns, file_name, pattern, 1, 0);
    printf("%zu\n", num_of_patterns);
    return 0;
}
