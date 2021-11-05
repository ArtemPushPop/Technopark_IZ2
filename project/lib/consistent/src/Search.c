#include <string.h>
#include "CodingFeatures.h"


int FindSymbolInMap(size_t *number_finded, const char map[], size_t size, const char symbols[], size_t coding) {
    size_t sym_size = strlen(symbols);
    size_t j;
    for (size_t i = 0; i * coding < size; i++) {
        j = 0;
        while ((j * coding < sym_size) && (!CompareWithCoding(map + coding * i, symbols + coding * j, coding)))
            j++;
        if (j * coding != sym_size)
            (*number_finded)++;
    }
    return 0;
}
