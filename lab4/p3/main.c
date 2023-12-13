#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5

int buffer[BUFFER_SIZE];
int count = 0;  // 현재 버퍼에 있는 아이템 수
int in = 0;     // 생산자가 다음에 아이템을 넣을 위치
int out = 0;    // 소비자가 다음에 아이템을 꺼낼 위치

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t full = PTHREAD_COND_INITIALIZER;
pthread_cond_t empty = PTHREAD_COND_INITIALIZER;

void *producer(void *arg) {
    int item;

    for (int i = 0; i < 5; i++) {
        item = rand() % 5+1;  // 임의의 아이템 생성

        pthread_mutex_lock(&mutex);

        while (count == BUFFER_SIZE) {
            // 버퍼가 가득 찼으면 대기
            pthread_cond_wait(&full, &mutex);
        }

        buffer[in] = item;
        in = (in + 1) % BUFFER_SIZE;
        count++;

        printf("Produced: %d\n", item);

        pthread_cond_signal(&empty);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

void *consumer(void *arg) {
    int item;

    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&mutex);

        while (count == 0) {
            // 버퍼가 비어 있으면 대기
            pthread_cond_wait(&empty, &mutex);
        }

        item = buffer[out];
        out = (out + 1) % BUFFER_SIZE;
        count--;

        printf("Consumed: %d\n", item);

        pthread_cond_signal(&full);
        pthread_mutex_unlock(&mutex);
    }

    pthread_exit(NULL);
}

int main() {
    pthread_t producer_thread, consumer_thread;

    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);

    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);

    return 0;
}
