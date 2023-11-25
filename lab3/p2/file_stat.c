#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdlib.h> // 추가된 헤더

int main(int argc, char *argv[]) {

    struct stat buf;
    char *msg;

    if (argc < 2) {
        fprintf(stderr, "Usage: file_type filename\n"); // 수정된 부분: 에러 메시지가 누락되어 추가
        exit(1);
    }

    if (lstat(argv[1], &buf) < 0) { // 수정된 부분: lstat 함수에 올바른 인자 전달
        perror("lstat");
        exit(1);
    }

    if (S_ISREG(buf.st_mode)) {
        msg = "regular file";
    } else {
        msg = "other type of file"; // 수정된 부분: 파일 타입이 정규 파일이 아닌 경우 처리
    }

    printf("\"%s\" is %s\n", argv[1], msg); // 수정된 부분: 출력 형식 수정

    return 0; // 추가된 부분: main 함수가 int를 반환하도록 변경
}
