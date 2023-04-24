#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int num_pipes = 3; // Number of pipes
    int pipes[num_pipes][2]; // Array to store pipe file descriptors

    // Create pipes
    for (int i = 0; i < num_pipes; i++) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(1);
        }
    }

    // Create child processes
    for (int i = 0; i < num_pipes; i++) {
        pid_t pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(1);
        } else if (pid == 0) {
            // Child process
            if (i == 0) {
                // First child process
                close(pipes[i][0]); // Close read end of first pipe
                dup2(pipes[i][1], STDOUT_FILENO); // Redirect stdout to write end of first pipe
                close(pipes[i][1]); // Close write end of first pipe

                // Execute command 1
                execlp("command1", "command1", NULL);
                perror("exec1");
                _exit(1);
            } else if (i == num_pipes - 1) {
                // Last child process
                close(pipes[i-1][1]); // Close write end of previous pipe
                dup2(pipes[i-1][0], STDIN_FILENO); // Redirect stdin to read end of previous pipe
                close(pipes[i-1][0]); // Close read end of previous pipe

                // Execute command 3
                execlp("command3", "command3", NULL);
                perror("exec3");
                _exit(1);
            } else {
                // Middle child processes
                close(pipes[i-1][1]); // Close write end of previous pipe
                dup2(pipes[i-1][0], STDIN_FILENO); // Redirect stdin to read end of previous pipe
                close(pipes[i-1][0]); // Close read end of previous pipe

                close(pipes[i][0]); // Close read end of current pipe
                dup2(pipes[i][1], STDOUT_FILENO); // Redirect stdout to write end of current pipe
                close(pipes[i][1]); // Close write end of current pipe

                // Execute command 2
                execlp("command2", "command2", NULL);
                perror("exec2");
                _exit(1);
            }
        }
    }

    // Close all pipe file descriptors in parent process
    for (int i = 0; i < num_pipes; i++) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Wait for all child processes to finish
    int status;
    pid_t pid;
    while ((pid = waitpid(-1, &status, 0)) != -1) {
        if (WIFEXITED(status)) {
            printf("Process %d exited with status %d\n", pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Process %d terminated by signal %d\n", pid, WTERMSIG(status));
        }
    }

    return 0;
}