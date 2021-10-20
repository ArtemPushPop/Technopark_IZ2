#include "main.h"
#include "CountSymbols.h"

#include <stdio.h>


int main(){
    char file_name[] = DATA_FILE;
    char pattern[] = "ab";
    size_t num_of_patterns = 0;
    FindNumSymbols(&num_of_patterns, file_name, pattern, 1, 0);
    printf("%zu", num_of_patterns);
    return 0;
}
