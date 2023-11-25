#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_TEXT 512
#define SERVER_MSG_TYPE 1
#define CLIENT_MSG_TYPE 2

struct msg_buffer {
    long mtype;
    char mtext[MAX_TEXT];
};

int main() {
    key_t key;
    int msgid;
    struct msg_buffer message;

    // 키 생성
    key = ftok("chat_program", 65);
    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // 메시지 큐 생성 또는 열기
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Server: Chat server started. Waiting for messages...\n");

    // 메시지 큐에서 메시지 수신
    while (1) {
        if (msgrcv(msgid, (void*)&message, MAX_TEXT, CLIENT_MSG_TYPE, 0) == -1) {
            perror("msgrcv");
            exit(EXIT_FAILURE);
        }

        // 수신된 메시지 출력
        printf("Client: %s", message.mtext);

        // 종료 조건
        if (strncmp(message.mtext, "exit", 4) == 0) {
            printf("Server: Chat server exiting.\n");
            break;
        }
    }

    // 메시지 큐 제거
    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("msgctl");
        exit(EXIT_FAILURE);
    }

    return 0;
}
