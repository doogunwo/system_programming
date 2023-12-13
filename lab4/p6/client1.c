#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#define SERVER_IP "127.0.0.1"
#define PORT 5000

int main() {
    int client_sock;
    struct sockaddr_in server_addr;
    char buffer[1024];

    // 클라이언트 소켓 생성
    if ((client_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 서버 주소 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr(SERVER_IP);

    // 서버에 연결
    if (connect(client_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server. Type 'exit' to quit.\n");

    while (1) {
        // 키보드 입력 받기
        printf("Enter message: ");
        fgets(buffer, sizeof(buffer), stdin);

        // 종료 조건 확인
        if (strncmp(buffer, "exit", 4) == 0) {
            break;
        }

        // 서버로 메시지 전송   
        send(client_sock, buffer, strlen(buffer), 0);
    }

    // 소켓 닫기
    close(client_sock);

    return 0;
}
