#pragma once


#include <unistd.h>


struct pm{
    pid_t *pid;
    size_t *map_size;
    char **map;
};


int _free_map(size_t , char **, size_t *);
int FindNumSymbols(size_t *, const char [], const char[], size_t , size_t , size_t );
int MapAndSearch(size_t *, const int, const char[], size_t , size_t , size_t , size_t );
size_t find_pid(pid_t , const pid_t [], size_t );

