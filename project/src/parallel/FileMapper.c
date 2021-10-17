#include "FileMapper.h"
#include "ProcessFunctions.h"
#include "MyMsg.h"


#include <sys/sysinfo.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <memory.h>



int free_map(size_t num_allocated, char **mapping, size_t *map_size){
    for (size_t i = 0; i < num_allocated; i++){
        munmap(mapping[i], map_size[i]);
        mapping[i] = NULL;
    }
    return 0;
}


int FindNumSymbols(size_t *num_of_symbols, const char file_path[], const char symbols[], size_t coding, size_t procs, size_t memory_available){
    struct sysinfo si;
    sysinfo(&si);
    size_t page = getpagesize();

    *num_of_symbols = 0;

    if (coding == 0){
        return -1; //неправильное количество байт кодировки.
    }
    if (procs == 0)
        procs = get_nprocs();
    if (memory_available == 0)
        memory_available = si.freeram / 2;
    if ((memory_available < coding) || (memory_available < page))
        return -2; // слишком мало памяти для загрузки

    size_t map_one_proc = (memory_available / procs / page) * page;

    int fd;
    if ((fd = open(file_path, O_RDONLY)) == -1)
        return -1; //не удалось открыть файл.
    struct stat st;
    stat(file_path, &st);
    size_t file_len = st.st_size;

    //нормализация исковых данных (фифифф) -> (фи)

    if (MapAndSearch(num_of_symbols, fd, symbols, file_len, coding, procs, map_one_proc) == 0) {
        close(fd);
        return 0;
    }
    else{
        close(fd);
        return -1; //произошла ошибка
    }

    //выравнять память для одного процесса по кодировке
}


int MapAndSearch(size_t *num_of_symbols, const int fd, const char symbols[], size_t fd_length, size_t coding, size_t procs, size_t map_one_proc){
    struct pm pm;
    pm.pid = (int *) malloc(sizeof(int) * procs);
    pm.map = (char **) malloc(sizeof(char *) * procs);
    pm.map_size = (size_t *) malloc(sizeof(size_t) * procs);
    memset(pm.map_size, 0, sizeof(int) * procs);
    memset(pm.pid, 0, sizeof(int) * procs);


    //загрузим возможную часть файла в память
    size_t i = 0;
    int e_o_f = 0;
    while(i < procs && !e_o_f){
        if (fd_length > map_one_proc){
            pm.map[i] = mmap(NULL, map_one_proc, PROT_READ, MAP_PRIVATE, fd, i * map_one_proc);
            pm.map_size[i] = map_one_proc;
            fd_length -= map_one_proc;
        }
        else{
            pm.map[i] = mmap(NULL, fd_length, PROT_READ, MAP_PRIVATE, fd, i * map_one_proc);
            pm.map_size[i] = fd_length;
            e_o_f = 1;
        }
        if (pm.map[i] == MAP_FAILED) {
            free_map(i, pm.map, pm.map_size);
            return -1;
        }
        i++;
    }
    size_t file_offset = i;

    //создаем очередь сообщений
    int msgqid;
    if ((msgqid = msgget(IPC_PRIVATE, IPC_CREAT|0660)) == -1){
        free_map(i, pm.map, pm.map_size);
    }

    //раздаем начальные работы
    i = 0;
    pid_t pid = 1;
    while ((i < procs) && (pm.map_size[i] != 0) && (pid > 0)) {
        if ((pid = fork()) < 0) {
            // обработка ошибки запуска процесса.
            // исключение создания зомбей.
            return -1;
        }
        else if (pid == 0)
            FindSymbolInMap(pm.map[i], pm.map_size[i], symbols, coding, msgqid);
        else{
            pm.pid[i] = pid;
            i++;
        }
    }
    size_t num_processes = i;

    //цикл раздачи новых работ, пока не будет обработан весь файл.
    int status;
    char *end = NULL;
    struct my_msgbuf buf;
    // file_offset ранее полученная переменная, для итерации по файлу, отображающая его смещение.
    while (num_processes != 0){
        pid = wait(&status);
        msgrcv(msgqid, (struct msgbuf *) &buf, MAX_SEND_SIZE, MSG_TYPE, IPC_NOWAIT);
        *num_of_symbols += strtol(buf.mtext, &end, 10);

        i = find_pid(pid, pm.pid, procs);
        pm.pid[i] = 0;
        munmap(pm.map[i], pm.map_size[i]);
        pm.map[i] = NULL;
        pm.map_size[i] = 0;
        if (!e_o_f){
            if (fd_length > map_one_proc){
                pm.map[i] = mmap(NULL, map_one_proc, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, file_offset * map_one_proc);
                pm.map_size[i] = map_one_proc;
                fd_length -= map_one_proc;
            }
            else{
                pm.map[i] = mmap(NULL, fd_length, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, file_offset * map_one_proc);
                pm.map_size[i] = fd_length;
                e_o_f = 1;
            }
            if (pm.map[i] == MAP_FAILED) {
                //обработка ошибки
//                free_map(i, pm.map, pm.map_size);
//                return -1;
            }
            file_offset++;
            if ((pid = fork()) < 0) {
                // обработка ошибки запуска процесса.
                // исключение создания зомбей.
                return -1;
            }
            else if (pid == 0)
                FindSymbolInMap(pm.map[i], pm.map_size[i], symbols, coding, msgqid);
        }
        else
            num_processes--;
    }
    return 0;
}



size_t find_pid(pid_t pid, const pid_t pid_array[], size_t processes){
    for (size_t i = 0; i < processes; i++){
        if (pid == pid_array[i])
            return i;
    }
    return processes;
}
