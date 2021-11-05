#include <iostream>
#include "gtest/gtest.h"


extern "C" {
#include "FileMapper.h"
#include "ProcessFunctions.h"
#include "Errors.h"
#include "MyMsg.h"
#include <sys/msg.h>
#include <fcntl.h>
}

class TestParallelSearchFixture : public testing::Test {
protected:
    void SetUp() override{
        if ((msgqid = msgget(IPC_PRIVATE, IPC_CREAT|0660)) == -1){
            exit(1);
        }
    }
    void TearDown() override{
        msgctl(msgqid, IPC_RMID, NULL);
    }
    const size_t num_of_tests = 4;
    const char *map[4] = {"abababab", "1223334444", "\n\n\n\n", ""};
    const size_t size_map[4] = {8, 10, 4, 0};
    const char *symbols[4] = {"a", "12", "abdl", "df"};
    const size_t result[4] = {4, 3, 0, 0};
    int msgqid;
};


TEST_F(TestParallelSearchFixture, FindSymbolInMap) {
    my_msgbuf buf;
    char *end;
    int st;
    pid_t pid;
    size_t num_of_symbols = 0;
    for (size_t i = 0; i < num_of_tests; i++){
        pid = fork();
        if (pid == 0)
            FindSymbolInMap(map[i], size_map[i], symbols[i], 1, msgqid);

        wait(&st);
        msgrcv(msgqid, (struct msgbuf *) &buf, MAX_SEND_SIZE, MSG_TYPE, IPC_NOWAIT);
        num_of_symbols = strtol(buf.mtext, &end, 10);
        EXPECT_EQ(num_of_symbols, result[i]);
    }

    // test conding not 1
    pid = fork();
    if (pid == 0)
        FindSymbolInMap(map[1], size_map[1], symbols[1], 2, msgqid);
    wait(&st);
    msgrcv(msgqid, (struct msgbuf *) &buf, MAX_SEND_SIZE, MSG_TYPE, IPC_NOWAIT);
    num_of_symbols = strtol(buf.mtext, &end, 10);
    EXPECT_EQ(num_of_symbols, 1);

    pid = fork();
    if (pid == 0)
        FindSymbolInMap(map[0], size_map[0], symbols[2], 2, msgqid);
    wait(&st);
    msgrcv(msgqid, (struct msgbuf *) &buf, MAX_SEND_SIZE, MSG_TYPE, IPC_NOWAIT);
    num_of_symbols = strtol(buf.mtext, &end, 10);
    EXPECT_EQ(num_of_symbols, 4);
}


class TestParallelMapFixture : public testing::Test {
protected:
    void SetUp() override {
        fd1 = open(valid_file_name.c_str(), O_RDONLY);
        fd2 = open(+ "file2.txt", O_RDONLY);
        if (fd2 == -1){
            close(fd1);
            exit(1);
        }
        if (fd1 == -1)
            exit(1);

        struct stat st;
        stat(valid_file_name.c_str(), &st);
        f1_len = st.st_size;
        stat(+ "file2.txt", &st);
        f2_len = st.st_size;

        page = getpagesize();
        valid_memory = page * 4;
    }
    void TearDown() override {
        close(fd1);
        close(fd2);
    }
    const std::string valid_file_name = "file1.txt";
    const std::string invalid_file_name = "invalid_file.txt";

    const size_t valid_coding = 1;
    const size_t invalid_coding = 3;

    size_t valid_memory;
    const size_t invalid_memory = 3;

    const char *symbols = "abb";
    const char *symbols_for_mmap = "b";

    int fd1, fd2;
    size_t f1_len, f2_len;
    size_t page;
};


TEST_F(TestParallelMapFixture, FindNumSymbols) {
    size_t num_of_symbols = 0;
    EXPECT_EQ(ERROR_OPEN_FILE, FindNumSymbols(&num_of_symbols, invalid_file_name.c_str(),
                                                    symbols, valid_coding, 0));
    EXPECT_EQ(ERROR_RAM, FindNumSymbols(&num_of_symbols, valid_file_name.c_str(),
                                                    symbols, valid_coding, invalid_memory));
    EXPECT_EQ(BAD_CODING, FindNumSymbols(&num_of_symbols, valid_file_name.c_str(),
                                                    symbols, invalid_coding, 0));
    EXPECT_EQ(0, FindNumSymbols(&num_of_symbols, valid_file_name.c_str(),
                                         symbols, 0, valid_memory));
}


TEST_F(TestParallelMapFixture, MmapAndSearch){
    size_t num_of_symbols = 0;
    EXPECT_EQ(ERROR_MAP, MapAndSearch(&num_of_symbols, fd1, symbols, f1_len, valid_coding, 2, invalid_memory));
    num_of_symbols = 0;
    EXPECT_EQ(0, MapAndSearch(&num_of_symbols, fd2, symbols_for_mmap, f2_len, valid_coding, 1, valid_memory));
    EXPECT_EQ(num_of_symbols, 4);
}



TEST(TestParallelUtils, ProperFree){
    struct process_map pm;
    pm.pid = (pid_t *)malloc(sizeof(pid_t));
    pm.map = (char **)malloc(sizeof(char*));
    pm.map_size = (size_t *)malloc(sizeof(size_t));
    pm.map_size[0] = 0; //необходимо для правильной очистки памяти.
    allfree(0, &pm);
    EXPECT_EQ(pm.map_size, nullptr);
    EXPECT_EQ(pm.map, nullptr);
    EXPECT_EQ(pm.pid, nullptr);
}


int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}