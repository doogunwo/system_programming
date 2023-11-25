#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, char *argv[]) {
    int fd;
    off_t size;

    if (argc < 2) {
        fprintf(stderr, "Usage: file_size filename\n");
        exit(EXIT_FAILURE);
    }

    if ((fd = open(argv[1], O_RDONLY)) == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    size = lseek(fd, 0, SEEK_END);

    if (size == -1) {
        perror("lseek");
        close(fd); // 파일을 열었으면 반드시 닫아주어야 합니다.
        exit(EXIT_FAILURE);
    }

    printf("%s's size = %ld\n", argv[1], size); // %d -> %ld로 수정
    close(fd);

    return 0;
}
