#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <errno.h>

#define MAX_CLIENTS 10
#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int server_socket, client_sockets[MAX_CLIENTS];
    fd_set read_fds, all_fds;
    int max_socket, activity, i, valread;
    struct sockaddr_in server_addr, client_addr;
    char buffer[BUFFER_SIZE];

    // 초기화
    for (i = 0; i < MAX_CLIENTS; i++) {
        client_sockets[i] = 0;
    }

    // 서버 소켓 생성
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 서버 주소 설정
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 서버 소켓에 주소 바인딩
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // 리스닝 시작
    if (listen(server_socket, 5) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    printf("Server: listening on port %d\n", PORT);

    FD_ZERO(&all_fds);
    FD_SET(server_socket, &all_fds);
    max_socket = server_socket;

    while (1) {
        read_fds = all_fds;
        activity = select(max_socket + 1, &read_fds, NULL, NULL, NULL);

        if ((activity < 0) && (errno != EINTR)) {
            perror("select");
            exit(EXIT_FAILURE);
        }

        // 새로운 연결 수락
        if (FD_ISSET(server_socket, &read_fds)) {
            int new_socket;
            if ((new_socket = accept(server_socket, (struct sockaddr *)&client_addr, (socklen_t *)&client_addr)) == -1) {
                perror("accept");
                exit(EXIT_FAILURE);
            }

            printf("Server: new connection, socket fd is %d, IP is : %s, port : %d\n",
                   new_socket, inet_ntoa(client_addr.sin_addr), ntohs(client_addr.sin_port));

            // 새로운 연결을 기존 소켓 집합에 추가
            for (i = 0; i < MAX_CLIENTS; i++) {
                if (client_sockets[i] == 0) {
                    client_sockets[i] = new_socket;
                    FD_SET(new_socket, &all_fds);
                    if (new_socket > max_socket) {
                        max_socket = new_socket;
                    }
                    break;
                }
            }
        }

        // 클라이언트로부터 데이터 수신 및 에코
        for (i = 0; i < MAX_CLIENTS; i++) {
            int client_socket = client_sockets[i];
            if (FD_ISSET(client_socket, &read_fds)) {
                valread = read(client_socket, buffer, BUFFER_SIZE);
                if (valread == 0) {
                    // 클라이언트 연결 종료
                    printf("Server: client disconnected, socket fd is %d\n", client_socket);
                    close(client_socket);
                    FD_CLR(client_socket, &all_fds);
                    client_sockets[i] = 0;
                } else {
                    // 클라이언트에게 데이터 에코
                    buffer[valread] = '\0';
                    printf("Server: received data from %d: %s", client_socket, buffer);
                    send(client_socket, buffer, strlen(buffer), 0);
                }
            }
        }
    }

    return 0;
}
