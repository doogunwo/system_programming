#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
    pid_t pid;

    if ((pid = fork()) < 0) {
        perror("fork failed");
    }

    if (pid == 0) {
        // 자식 프로세스
        execl("/bin/ls", "ls", "-l", (char *)0);
        perror("execl failed");
        exit(EXIT_FAILURE); // execl이 성공하지 못하면 프로세스를 종료해야 합니다.
    } else if (pid > 0) {
        // 부모 프로세스
        wait(NULL); // 자식 프로세스의 종료를 기다림
        printf("ls completed\n");
        exit(0);
    } else {
        perror("fork failed");
        exit(EXIT_FAILURE);
    }

    return 0;
}
