#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

int test(const char *filename)
{
    struct stat file_stat;

    if (stat(filename, &file_stat) < 0) {
        perror("stat");
        return -1;
    }

    printf("File: %s\n", filename);
    printf("Size: %ld bytes\n", (long)file_stat.st_size);
    printf("File type: ");

    if (S_ISREG(file_stat.st_mode)) {
        printf("Regular File\n");
    } else if (S_ISDIR(file_stat.st_mode)) {
        printf("Directory\n");
    } else if (S_ISLNK(file_stat.st_mode)) {
        printf("Symbolik link\n");
    } else {
        printf("Other\n");
    }

    return 0;
}

int main(int argc, char *argv[])
{
    if (argc != 2) {
        printf("Usage: %s filename\n", argv[0]);
        return 1;
    }

    int ret = test(argv[1]);
    if (ret < 0) {
        printf("error test\n");
        return 1;
    }
    return 0;
}



