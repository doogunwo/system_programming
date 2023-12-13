#include <stdio.h>
#include <pthread.h>

void *hello_thread(void *arg){
    printf("Thread: Hello, World\n");
    return arg;
}

int main(){
    pthread_t tid; // 'pthread'를 'pthread_t'로 수정
    int status;

    status = pthread_create(&tid, NULL, hello_thread, NULL);
    if(status != 0){
        perror("Create thread");
    }
    pthread_exit(NULL);
}
