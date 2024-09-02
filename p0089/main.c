#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    pid_t pid;
    int status;

    // Data to be passed to the new process via environment variables
    char *data = "Hello from parent!";
    char *envp[] = {
        "MY_DATA=Hello from parent!",
        NULL
    };

    // Fork the process
    pid = fork();

    if (pid < 0) {
        // Fork failed
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (pid == 0) {
        // Child process
        printf("Child process (PID: %d) will now execute a new program.\n", getpid());

        // Prepare arguments for execve
        char *argv[] = { "print_env", NULL}; 

        // Execute a new program (assuming 'print_env' is available and prints environment variables)
        if (execve("./print_env", argv, envp) == -1) {
            perror("execve");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        printf("Parent process (PID: %d) waiting for child to complete.\n", getpid());

        // Wait for the child process to complete
        if (waitpid(pid, &status, 0) == -1) {
            perror("waitpid");
            exit(EXIT_FAILURE);
        }

        // Check if the child process exited normally
        if (WIFEXITED(status)) {
            printf("Child process exited with status %d.\n", WEXITSTATUS(status));
        } else {
            printf("Child process did not terminate normally.\n");
        }
    }

    return 0;
}

