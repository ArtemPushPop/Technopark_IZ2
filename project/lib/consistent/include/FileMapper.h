#pragma once


#include <unistd.h>


int FindNumSymbols(size_t *num_of_symbols, const char *file_path, const char symbols[], size_t coding, size_t memory_available);
int MmapAndSearch(size_t *num_of_symbols, int fd, size_t, const char symbols[], size_t coding, size_t memory_available);
