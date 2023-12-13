#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

#define num_th 3

void *hello_thread(void *arg){
    int id = (int)arg; // 포인터로 전달된 값을 정수로 형변환
    printf("Th %d: hello world\n", id);
    return arg;
}

int main(){
    pthread_t tid[num_th];
    int status;

    for (int i = 0; i < num_th; i++){
        status = pthread_create(&tid[i], NULL, hello_thread, (void *)i);
        if(status != 0){
            fprintf(stderr, "Create th %d: %d\n", i, status);
            exit(1);
        }
    }

    pthread_exit(NULL);
}
