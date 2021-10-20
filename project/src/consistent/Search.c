#include <string.h>


int FindSymbolInMap(size_t * number_finded, const char map[], size_t size, const char symbols[], size_t coding){
    size_t sym_size = strlen(symbols);
    size_t j;
    size_t code_iter;
    int finded;
    if (coding == 1) {
        for (size_t i = 0; i < size; i++) {
            j = 0;
            while ((j < sym_size) && (map[i] != symbols[j]))
                j++;
            if (j != sym_size)
                (*number_finded)++;
        }
    }
    else
        for (size_t i = 0; i < size / coding; i++) {
            j = 0;
            finded = 0;
            while ((j < sym_size / coding) && !finded){
                code_iter = 0;
                while ((code_iter < coding) && (map[i * coding + code_iter] == symbols[j * coding + code_iter]))
                    code_iter++;
                if (code_iter == coding){
                    (*number_finded)++;
                    finded = 1;
                }
                j++;
            }
        }

    return 0;
}
