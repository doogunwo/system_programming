#include <stdio.h>
#include <stdlib.h> // 추가된 헤더
#include <string.h>
#include <unistd.h>

#define MAX_BUF 256

int main(int argc, char *argv[]) {

    char buf[MAX_BUF];

    if (argc < 2) {
        fprintf(stderr, "Usage: change_directory dirname\n"); // 수정된 부분: 에러 메시지가 누락되어 추가
        exit(1);
    }

    memset(buf, 0, MAX_BUF);

    if (getcwd(buf, MAX_BUF) == NULL) { // 수정된 부분: getcwd의 반환값을 확인하여 오류 처리
        perror("getcwd");
        exit(1);
    }

    printf("working dir (before) = %s\n", buf);

    if (chdir(argv[1]) < 0) {
        perror("chdir");
        exit(1);
    }

    memset(buf, 0, MAX_BUF);

    if (getcwd(buf, MAX_BUF) == NULL) { // 수정된 부분: getcwd의 반환값을 확인하여 오류 처리
        perror("getcwd");
        exit(1);
    }

    printf("working dir (after) = %s\n", buf);

    return 0; // 추가된 부분: main 함수가 int를 반환하도록 변경
}
