#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *cancle_thread(void *arg){
    int i, state;
    for(i = 0; ; i++){
        pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, &state);
        printf("th cancel disabled\n");
        sleep(1);
        pthread_setcancelstate(state, &state);
        printf("th cancel restored\n");
    }
    return arg;
}

int main(int argc, char *argv[]){
    pthread_t tid;
    int status;

    if(argc < 2){
        fprintf(stderr, "usage: %s time(sec)\n", argv[0]);
        exit(1);
    }

    status = pthread_create(&tid, NULL, cancle_thread, NULL);
    if(status != 0){
        fprintf(stderr, "create th: %d\n", status);
        exit(1);
    }

    sleep(atoi(argv[1]));  // 대기 시간 동안 기다린 후 메인 쓰레드 종료

    // 취소 요청
    status = pthread_cancel(tid);
    if(status != 0){
        fprintf(stderr, "cancel th: %d\n", status);
        exit(1);
    }

    // 쓰레드 조인
    status = pthread_join(tid, NULL);
    if(status != 0){
        fprintf(stderr, "join th: %d\n", status);
        exit(1);
    }

    return 0;
}
