#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <semaphore.h>

#define SHM_SIZE 1024

int main(int argc, char *argv[]) {
    char *shm_ptr;
    int source_fd, destination_fd;
    sem_t *sem;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <source_file> <destination_file>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char *source_file = argv[1];
    char *destination_file = argv[2];

    // 세마포어 생성 또는 연결
    sem = sem_open("/mysemaphore", O_CREAT | O_EXCL, 0666, 1);
    if (sem == SEM_FAILED) {
        perror("sem_open");
        exit(EXIT_FAILURE);
    }

    // 공유 메모리 파일 매핑
    source_fd = open(source_file, O_RDONLY);
    if (source_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // 공유 메모리 파일 생성 및 크기 설정
    destination_fd = open(destination_file, O_RDWR | O_CREAT | O_TRUNC, 0666);
    if (destination_fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }
    ftruncate(destination_fd, SHM_SIZE);

    // 공유 메모리 파일 매핑
    shm_ptr = mmap(NULL, SHM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, destination_fd, 0);
    if (shm_ptr == MAP_FAILED) {
        perror("mmap");
        exit(EXIT_FAILURE);
    }

    // 파일 내용을 공유 메모리로 복사
    ssize_t read_size;
    while ((read_size = read(source_fd, shm_ptr, SHM_SIZE)) > 0) {
        sem_wait(sem);
        sem_post(sem);
    }

    // 메모리 및 세마포어 정리
    munmap(shm_ptr, SHM_SIZE);
    close(source_fd);
    close(destination_fd);
    sem_close(sem);
    sem_unlink("/mysemaphore");

    return 0;
}
