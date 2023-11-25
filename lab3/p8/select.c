#include <sys/time.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h> // 추가: exit 함수를 사용하기 위한 헤더 파일

#define MSGSIZE 16

char *hello_msg = "Hello, parent"; // ';' 추가
char *bye_msg = "Bye, parent"; // ';' 추가

void parent(int [3][2]);
void child(int [2]);

int main() {
    int pp[3][2], i;
    int pid;

    for (i = 0; i < 3; i++) {
        if (pipe(pp[i]) == -1) { // '==='를 '=='로 수정
            perror("pipe call failed");
            exit(1);
        }
        pid = fork();
        if (pid == 0) {
            child(pp[i]);
        } else if (pid == -1) {
            perror("fork failed");
            exit(1);
        }
    }

    parent(pp);
}

void parent(int pp[3][2]) {
    int i;
    char buf[MSGSIZE];

    for (i = 0; i < 3; i++) {
        close(pp[i][1]); // 부모 프로세스에서 쓰기 파일 디스크립터를 닫음
        read(pp[i][0], buf, MSGSIZE);
        printf("%s\n", buf);
        close(pp[i][0]); // 읽기 파일 디스크립터를 닫음
    }

    printf("%s\n", bye_msg);
}

void child(int p[2]) {
    close(p[0]); // 자식 프로세스에서 읽기 파일 디스크립터를 닫음
    write(p[1], hello_msg, MSGSIZE);
    close(p[1]); // 쓰기 파일 디스크립터를 닫음
    exit(0); // 추가: 자식 프로세스가 종료되도록 함
}
