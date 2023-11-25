#include <stdio.h>
#include <stdlib.h> // 추가된 헤더
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int fd;
    const char *buf = "this is a test."; // 수정된 부분: 문자열을 수정할 수 없게 const로 변경

    ssize_t cnt;
    int flags = O_WRONLY | O_CREAT | O_TRUNC;
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    if (argc < 2) {
        fprintf(stderr, "USAGE: file_create filename\n");
        exit(EXIT_FAILURE); // 수정된 부분: exit 코드를 EXIT_FAILURE로 변경
    }

    if ((fd = open(argv[1], flags, mode)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    cnt = write(fd, buf, strlen(buf));
    if (cnt == -1) { // 추가된 부분: write 함수 오류 처리
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("write count = %zd\n", cnt); // 수정된 부분: %d 대신 %zd를 사용하여 ssize_t 값 출력
    close(fd);

    return 0; // 추가된 부분: main 함수가 int를 반환하도록 변경
}
