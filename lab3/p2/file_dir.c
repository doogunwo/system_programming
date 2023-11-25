#include <stdio.h>
#include <stdlib.h> // 추가된 헤더
#include <sys/types.h>
#include <dirent.h>

int main(int argc, char *argv[]) {

    DIR *pdir;
    struct dirent *pde;
    int i = 0;

    if (argc < 2) {
        fprintf(stderr, "Usage: see_directory dirname\n"); // 수정된 부분: 에러 메시지가 누락되어 추가
        exit(1);
    }

    if ((pdir = opendir(argv[1])) == NULL) { // 수정된 부분: opendir의 반환값을 확인
        perror("opendir");
        exit(1);
    }

    while ((pde = readdir(pdir)) != NULL) {
        printf("%20s ", pde->d_name);
        if (++i % 3 == 0) {
            printf("\n");
        }
    }
    printf("\n");

    closedir(pdir);

    return 0; // 추가된 부분: main 함수가 int를 반환하도록 변경
}
