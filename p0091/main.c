#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>

int main() {
    pid_t pid, ppid;

    // Create a new process
    pid = fork();
    
    if (pid < 0) {
        // Fork failed
        perror("fork");
        return 1;
    }
    
    if (pid == 0) {
        // Child process
        // Set the child process to be in its own process group
        if (setpgid(0, 0) < 0) { // setpgid(0, 0) sets the child process as the leader of a new process group
            perror("setpgid");
            return 1;
        }

        printf("Child process: PID = %d, PGID = %d\n", getpid(), getpgid(0));
        
        // Do some work here, e.g., run a command, etc.
        sleep(10); // Simulating some work
        
        return 0;
    } else {
        // Parent process
        ppid = getpid();
        printf("Parent process: PID = %d, PGID = %d\n", ppid, getpgid(0));
        
        // Wait for child process to complete
        wait(NULL);
    }

    return 0;
}

