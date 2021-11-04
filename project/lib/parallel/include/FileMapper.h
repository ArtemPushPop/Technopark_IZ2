#pragma once


#include <unistd.h>


struct process_map{
    pid_t *pid;
    size_t *map_size;
    char **map;
};


int allfree(size_t num_allocated, struct process_map *pm);
int FindNumSymbols(size_t *num_of_symbols, const char *file_path, const char symbols[],
                   size_t coding, size_t memory_available);
size_t DoMmap(size_t *fd_length, size_t map_one_proc, int fd, size_t file_offset, struct process_map *pm, size_t elem);
int MapAndSearch(size_t *num_of_symbols, const int fd, const char symbols[], size_t fd_length,
                 size_t coding, size_t procs, size_t map_one_proc);
size_t find_pid(pid_t pid, const pid_t pid_array[], size_t processes);
int termination(size_t num_allocated, struct process_map*pm, int msgqid);
int clear_all_processes();
