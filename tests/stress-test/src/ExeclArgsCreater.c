#include <string.h>


char * MakeCommand(char *cmd, size_t cmd_len, char *path, char *letters){
    cmd[cmd_len] = '\0';
    strcat(cmd, " -f ");
    strcat(cmd, path);
    strcat(cmd, " -p ");
    strcat(cmd, letters);
    strcat(cmd, " ");
    return cmd;
}


char * MakePath(char *path, const char* dir, const char *file_name){
    path[0] = '\0';
    strcat(path, dir);
    strcat(path, file_name);
    return path;
}
