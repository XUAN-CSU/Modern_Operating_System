#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>          // for open
#include <unistd.h>         // for read, close

//#define PATH "./test.txt"

int test(char *path)
{
    int fd = open(path, 0);
    if (-1 == fd) {
        perror("open");
        return -1;
    }
    
    char buffer[4] = {};
    int ret = read(fd, buffer, 3);
    close(fd);
    buffer[3] = '\0';

    printf("The read is : %s\n", buffer);
    return 0;
}


int main(int argc, char *argv[])
{

    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }
                
    int ret = test(argv[1]);
    
    return 0;
}

