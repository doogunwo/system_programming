#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *join(void *arg){
    pthread_exit(arg);
}

int main(int argc, char *argv[]){
    pthread_t tid;
    int arg, status;
    void *result;

    if(argc < 2){
        fprintf(stderr, "usage: %s number\n", argv[0]);
        exit(1);
    }

    arg = atoi(argv[1]);

    status = pthread_create(&tid, NULL, join, (void *)arg);
    if(status != 0){
        fprintf(stderr, "create th: %d\n", status);
        exit(1);
    }

    status = pthread_join(tid, &result);
    if(status != 0){
        fprintf(stderr, "join th : %d", status);
        exit(1);
    }

    return (int) result;
}
