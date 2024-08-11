#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>                 // for memset

int test(const char *filename)
{
    int fd = open(filename, O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    if (fd < 0) {
        perror("open");
        return -1;
    }

    const char data[] = "Hello, Shirley";
    int data_len = sizeof(data);

    ssize_t written = write(fd, data, data_len);
    if (written != data_len) {
        perror("write");
        close(fd);
        return -1;
    }

    off_t offset = lseek(fd,0, SEEK_SET);
    if (offset < 0) {
        perror("lseek");
        close(fd);
        return -1;
    }

    char rev[data_len + 1];
    memset(rev, 0, sizeof(rev));
    ssize_t bytesRead = read(fd, rev, data_len);
    if (bytesRead != data_len) {
        perror("read");
        close(fd);
        return -1;
    }

    rev[data_len] = '\0';
    printf(" Read from %s is : %s\n", filename, rev);
    return 0;
}

int main()
{
    char *filename = "lseek_test.txt";
    int ret = test(filename);
    if (ret < 0) {
        printf("Something wrong!\n");
        return -1;
    }
    return 0;
}
           

