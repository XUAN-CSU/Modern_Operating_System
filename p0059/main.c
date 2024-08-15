#include <stdio.h>
#include <sys/mount.h>
#include <errno.h>

int test_mount()
{
    const char *source = "/dev/sda1";
    const char *target = "/mnt/mydisk";
    const char *filesystemtype = "ext4";
    unsigned long mountflags = MS_RDONLY;
    const void *data = NULL;

    if (mount(source, target, filesystemtype, MS_RDONLY, data) == 0) {
        printf("Mount successful\n");
    } else {
        perror("Mount failed");
        return -1;
    }

    return 0;
}
   

int main()
{
    int ret = test_mount();

    return 0;
}
