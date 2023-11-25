#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    pid_t pid;

    printf("Calling fork\n");
    pid = fork();

    if (pid == 0) {
        printf("I'm the child process\n");
    } else if (pid > 0) {
        printf("I'm the parent\n");
    } else {
        printf("Fork failed\n");
    }

    return 0;
}
