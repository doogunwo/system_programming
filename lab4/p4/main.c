#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define MAX_CLIENTS 3
#define BUFFER_SIZE 256

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

char messages[MAX_CLIENTS][BUFFER_SIZE];
int message_flags[MAX_CLIENTS];
int num_clients = 0;
int current_client = 0;  // 현재 입력을 받을 클라이언트의 인덱스

void *client_thread(void *arg) {
    int client_id = *((int *)arg);
    free(arg);

    while (1) {
        pthread_mutex_lock(&mutex);

        // 현재 입력을 받을 차례인 클라이언트가 아니면 대기
        while (current_client != client_id) {
            pthread_cond_wait(&cond, &mutex);
        }

        char buffer[BUFFER_SIZE];
        printf("\nClient %d: Enter a message to send: ", client_id);
        fgets(buffer, BUFFER_SIZE, stdin);

        // 다음 클라이언트의 차례로 변경
        current_client = (current_client + 1) % num_clients;

        pthread_mutex_unlock(&mutex);

        sprintf(messages[client_id], "%s", buffer);
        message_flags[client_id] = 1;
        pthread_cond_broadcast(&cond);  // 다른 클라이언트 스레드들에게 신호 전달
    }
}

void *server_thread(void *arg) {
    while (1) {
        pthread_mutex_lock(&mutex);

        // 모든 클라이언트로부터 메시지 전송 요청을 기다림
        // 모든 클라이언트로부터 메시지 전송 요청을 기다림
        while (!message_flags[0] && !message_flags[1] && !message_flags[2]) {
            pthread_cond_wait(&cond, &mutex);
        }


        // 수신된 메시지를 출력하고 모든 클라이언트에게 방송
        for (int i = 0; i < num_clients; ++i) {
            if (message_flags[i]) {
                printf("\nServer: Client %d ,  %s", i, messages[i]);
                message_flags[i] = 0;
            }
        }

        pthread_mutex_unlock(&mutex);
    }
}

int main() {
    pthread_t server_tid;
    pthread_t client_tid[MAX_CLIENTS];

    // 서버 스레드 생성
    pthread_create(&server_tid, NULL, server_thread, NULL);

    // 클라이언트 스레드 생성
    for (int i = 0; i < MAX_CLIENTS; ++i) {
        int *client_id = malloc(sizeof(int));
        *client_id = i;
        pthread_create(&client_tid[i], NULL, client_thread, client_id);
        ++num_clients;
    }

    // 스레드 종료 대기
    pthread_join(server_tid, NULL);
    for (int i = 0; i < num_clients; ++i) {
        pthread_join(client_tid[i], NULL);
    }

    return 0;
}
