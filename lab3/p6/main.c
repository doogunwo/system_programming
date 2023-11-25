#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int mySystem(const char *command);

int main(int argc, char *argv[]){
    int result = mySystem(argv[1]);
    if (result == -1) {
        perror("my_system");
        return EXIT_FAILURE;
    }
    printf("명령어 반환값: %d\n", result);
    return EXIT_SUCCESS;

}

int mySystem(const char *command){

    pid_t child_pid;
    int status;

    if ((child_pid = fork()) == -1) {
        perror("fork");
        return -1;
    }

    if (child_pid == 0) {
        // 자식 프로세스에서 exec를 이용하여 명령어 실행
        if (execl("/bin/sh", "sh", "-c", command, (char *)NULL) == -1) {
            perror("execl");
            exit(EXIT_FAILURE);
        }
    } else {
        // 부모 프로세스에서 자식 프로세스의 종료를 기다림
        if (waitpid(child_pid, &status, 0) == -1) {
            perror("waitpid");
            return -1;
        }

        // 자식 프로세스의 반환값을 반환
        return WEXITSTATUS(status);
    }

    return 0;

}