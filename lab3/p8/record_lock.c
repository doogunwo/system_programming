#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define THIS_PROCESS 2
#define THAT_PROCESS 1

int main() {
    int fd;
    struct flock testlock;
    int len;
    char buf[20];

    testlock.l_type = F_RDLCK;
    testlock.l_whence = SEEK_SET;
    testlock.l_start = 0;  // 'L'이 아닌 'l'로 수정

    testlock.l_len = 0;

    fd = open("testlock", O_RDWR);  // 'P_RDWR'가 아닌 'O_RDWR'로 수정
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    if (fcntl(fd, F_SETLKW, &testlock) == -1) {
        perror("fcntl");
        exit(1);
    }

    printf("process %d: locked successfully\n", THIS_PROCESS);

    len = read(fd, buf, 20);
    printf("process %d: read %.*s from testlock\n", THIS_PROCESS, len, buf);

    printf("process %d: unlocking\n", THIS_PROCESS);
    testlock.l_type = F_UNLCK;
    if (fcntl(fd, F_SETLK, &testlock) == -1) {
        perror("fcntl");
        exit(1);
    }

    return 0;
}
