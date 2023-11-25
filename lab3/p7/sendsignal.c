#include <stdio.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h> // 추가: exit 함수를 사용하기 위한 헤더 파일

int i = 0;
void p_handler(int), c_handler(int);

int main() {
    pid_t pid, ppid;
    struct sigaction act;

    pid = fork();
    if (pid == 0) {
        act.sa_handler = c_handler;
        sigaction(SIGUSR1, &act, NULL);
        ppid = getppid();
        while (1) {
            sleep(1);
            kill(ppid, SIGUSR1);
            pause();
        }
    } else if (pid > 0) {
        act.sa_handler = p_handler;
        sigaction(SIGUSR1, &act, NULL);
        while (1) {
            pause();
            sleep(1);
            kill(pid, SIGUSR1);
        }
    } else {
        perror("Error");
        exit(EXIT_FAILURE); // 추가: fork 실패 시 프로그램 종료
    }

    return 0;
}

void p_handler(int signo) {
    printf("parent %d\n", i++);
}

void c_handler(int signo) {
    printf("child %d\n", ++i);
}
