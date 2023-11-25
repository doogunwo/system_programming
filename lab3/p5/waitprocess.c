/* waitprocess.c */ 
/* wait example */
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h> // 필요한 헤더 파일 추가

int main() {
    pid_t pid;
    int status, exit_status;

    if ((pid = fork()) < 0) {
        perror("fork failed");
    }

    if (pid == 0) {
        sleep(4); /* 수행을 4초 동안 중단 */
        exit(5);
    }

    if ((pid = wait(&status)) == -1) {
        perror("wait failed");
        exit(2);
    }

    if (WIFEXITED(status)) {
        exit_status = WEXITSTATUS(status);
        printf("Child process exited with status: %d\n", exit_status); // 수정: 상태 출력 추가
    }

    exit(0); // 수정: ' 뒤에 ; 추가
}
