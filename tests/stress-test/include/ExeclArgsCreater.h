#pragma once


#include <string.h>


char * MakeCommand(char *cmd, size_t cmd_len, char *path, char *letters);
char * MakePath(char *path, const char* dir, const char *file_name);
