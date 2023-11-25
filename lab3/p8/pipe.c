#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>  // 추가: exit 함수를 사용하기 위한 헤더 파일

#define MSGSIZE 16

char *msg[2] = { "Hello", "world" };

int main() {
    char buf[MSGSIZE];  // ';'이 누락된 것을 추가
    int p[2], i;

    if (pipe(p) == -1) {
        perror("pipe call failed");
        exit(1);
    }

    for (i = 0; i < 2; i++) {
        write(p[1], msg[i], MSGSIZE);
    }

    for (i = 0; i < 2; i++) {
        read(p[0], buf, MSGSIZE);
        printf("%s\n", buf);
    }

    return 0;
}
