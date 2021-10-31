#include "main.h"
#include "CountSymbols.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>


int main(int argc, char *argv[]){
    //обработка опций
    int opt;
    char *file_name = DATA_FILE;
    size_t coding = 1;
    char *pattern = "ab";
    char *opts = "f:p:c:";
    while ((opt = getopt(argc, argv, opts)) != -1){
        switch (opt) {
            case 'f' : file_name = optarg; break;
            case 'p' : pattern = optarg; break;
            case 'c' :
                coding = strtoul(optarg, NULL, 0);
                if (coding == 0)
                    return -1; // bad parameters
            default: break;
        }
    }

    size_t num_of_patterns = 0;
    FindNumSymbols(&num_of_patterns, file_name, pattern, coding, 0);
    printf("%zu\n", num_of_patterns);
    return 0;
}
