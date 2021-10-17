#include "FileMapper.h"
#include <stdio.h>
#include <sys/mman.h>


int main(){
    char file_name[] = "../data/data.txt";
    char pattern[] = "ab";
    size_t num_of_patterns = 0;
    FindNumSymbols(&num_of_patterns, file_name, pattern, 2, 0, 0);
    printf("%zu", num_of_patterns);
    return 0;
}
