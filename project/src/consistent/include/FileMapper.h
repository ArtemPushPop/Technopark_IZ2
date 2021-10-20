#pragma once


#include <unistd.h>


int FindNumSymbols(size_t *, const char [], const char[], size_t, size_t );
int MmapAndSearch(size_t *num_of_symbols, int fd, size_t, const char symbols[], size_t coding, size_t memory_available);
