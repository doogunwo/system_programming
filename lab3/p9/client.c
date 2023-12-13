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

    key = ftok("chat_program", 65);

    if (key == -1) {
        perror("ftok");
        exit(EXIT_FAILURE);
    }

    // 메시지 큐 ID 획득
    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("msgget");
        exit(EXIT_FAILURE);
    }

    printf("Client: Chat client started. Type 'exit' to exit.\n");

    while (1) {
        printf("You:");
        fgets(message.mtext, MAX_TEXT, stdin);
        message.mtype = CLIENT_MSG_TYPE;

        // 메시지 전송
        if (msgsnd(msgid, (void*)&message, MAX_TEXT, 0) == -1) {
            perror("msgsnd");
            exit(EXIT_FAILURE);
        }

        // 종료 조건
        if (strncmp(message.mtext, "exit", 4) == 0) {
            printf("Client: Exiting chat client.\n");
            break;
        }
    }

    return 0;
}
