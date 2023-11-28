#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        printf("Child process (PID=%d) is running...\n", getpid());
        sleep(2);
        printf("Child process is exiting...\n");
        exit(42);
    } else {
        // Parent process
        printf("Parent process (PID=%d) created child process (PID=%d)\n", getpid(), child_pid);

        // Parent sleeps to let the child process finish
        sleep(5);

        // Parent doesn't wait for the child, creating a zombie
        printf("Parent process is exiting without waiting for the child...\n");
        exit(EXIT_SUCCESS);
    }

    return 0;
}

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t child_pid = fork();

    if (child_pid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (child_pid == 0) {
        // Child process
        printf("Child process (PID=%d) is running...\n", getpid());
        sleep(2);
        printf("Child process is exiting...\n");
        exit(42);
    } else {
        // Parent process
        printf("Parent process (PID=%d) created child process (PID=%d)\n", getpid(), child_pid);

        // Parent sleeps briefly to let the child process start
        sleep(1);

        // Parent exits, leaving the child as an orphan
        printf("Parent process is exiting, leaving the child as an orphan...\n");
        exit(EXIT_SUCCESS);
    }

    return 0;
}
