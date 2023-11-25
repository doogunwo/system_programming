#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int fd;
    const char *buf = "this is a test."; // 수정된 부분: 문자열을 const로 변경

    ssize_t cnt;
    int flags = O_WRONLY | O_CREAT | O_APPEND; // 수정된 부분: O_APPEND 플래그 추가
    mode_t mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;

    if (argc < 2) {
        fprintf(stderr, "Usage: file_append filename\n");
        exit(EXIT_FAILURE);
    }

    if ((fd = open(argv[1], flags, mode)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    cnt = write(fd, buf, strlen(buf));
    if (cnt == -1) {
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("write count = %zd\n", cnt);
    close(fd);

    return 0;
}
