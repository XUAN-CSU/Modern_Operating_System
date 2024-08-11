#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>       // for the using wait();

int g_value = 100;          // child process will change the global value, but those changes will only be visible to the child process.

int main()
{
    int value = 10;

    printf("Before the fork() the value is %d\n", value);
    printf("Before the fork() the global value is %d\n", g_value);

    pid_t pid = fork();

    if (pid < 0) {
        perror("fork");
        return 1;
    } else if(0 == pid) {
        value = 20;
        g_value = 20;
        printf("Child process: value = %d (PID: %d)\n", value, getpid());
        printf("Child process: global value = %d (PID: %d)\n", g_value, getpid());
    } else {
        wait(NULL);
        printf("Parent prcess: value = %d (PID: %d)\n", value, getpid());
        printf("Parent prcess: global value = %d (PID: %d)\n", g_value, getpid());
    }
    printf("global value : %d\n", g_value);
    
    return 0;
}
