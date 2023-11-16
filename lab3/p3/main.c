#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>
void ls_R(const char *path, int depth);

int main(){

    const char *start_dir = "..";
    ls_R(start_dir,0);
    return 0;
}

void ls_R(const char *path, int depth){

    DIR *dir;
    struct dirent *entry;
    struct stat file_info;

    if ((dir = opendir(path)) == NULL) {
        perror("opendir");
        exit(EXIT_FAILURE);
    }

    while ((entry = readdir(dir)) != NULL) {
        char full_path[PATH_MAX];
        snprintf(full_path, sizeof(full_path), "%s/%s", path, entry->d_name);

        if (stat(full_path, &file_info) == -1) {
            perror("stat");
            exit(EXIT_FAILURE);
        }

        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            for (int i = 0; i < depth; i++) {
                printf("  "); // 간격을 주어서 디렉토리 계층을 표현합니다.
            }

            if (S_ISDIR(file_info.st_mode)) {
                printf("%s (d)\n", entry->d_name);
                // 디렉토리인 경우 재귀적으로 함수를 호출하여 내부의 파일과 디렉토리를 나열합니다.
                ls_R(full_path, depth + 1);
            } else {
                printf("%s (-)\n", entry->d_name);
            }
        }
    }

    closedir(dir);

}



