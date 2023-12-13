#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <errno.h>

#define PORT 5000
#define MAX_CLIENTS 10

int main() {
    int server_sock, client_socks[MAX_CLIENTS], max_clients = MAX_CLIENTS;
    struct sockaddr_in server_addr, client_addr;
    fd_set read_fds, master_fds;

    // 서버 소켓 생성
    if ((server_sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(EXIT_FAILURE);
    }

    // 서버 주소 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 소켓에 주소 할당
    if (bind(server_sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind");
        exit(EXIT_FAILURE);
    }

    // 클라이언트 연결 대기
    if (listen(server_sock, 5) == -1) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    // 초기화
    FD_ZERO(&master_fds);
    FD_SET(server_sock, &master_fds);
    int max_fd = server_sock;

    printf("Server started. Waiting for connections...\n");

    while (1) {
        read_fds = master_fds;

        // 변화된 파일 디스크립터 모니터링
        if (select(max_fd + 1, &read_fds, NULL, NULL, NULL) == -1) {
            perror("select");
            exit(EXIT_FAILURE);
        }

        // 새로운 연결 수락
        if (FD_ISSET(server_sock, &read_fds)) {
            int client_sock, client_len = sizeof(client_addr);
            if ((client_sock = accept(server_sock, (struct sockaddr *)&client_addr, &client_len)) == -1) {
                perror("accept");
                continue;
            }

            printf("New connection from %s on socket %d\n", inet_ntoa(client_addr.sin_addr), client_sock);

            // 새로운 클라이언트를 master_fd 집합에 추가
            FD_SET(client_sock, &master_fds);
            if (client_sock > max_fd) {
                max_fd = client_sock;
            }

            // 현재 연결된 클라이언트의 개수 확인
            int num_clients = 0;
            for (int i = 0; i < MAX_CLIENTS; ++i) {
                if (client_socks[i] != 0) {
                    num_clients++;
                }
            }

            printf("Number of clients: %d\n", num_clients);

            // 클라이언트 소켓을 배열에 저장
            for (int i = 0; i < MAX_CLIENTS; ++i) {
                if (client_socks[i] == 0) {
                    client_socks[i] = client_sock;
                    break;
                }
            }
        }

        // 클라이언트로부터 데이터 수신 및 처리
        for (int i = 0; i < max_clients; ++i) {
            int client_sock = client_socks[i];

            if (FD_ISSET(client_sock, &read_fds)) {
                char buffer[1024];
                int bytes_received;

                if ((bytes_received = recv(client_sock, buffer, sizeof(buffer), 0)) <= 0) {
                    // 클라이언트 연결이 끊어짐
                    printf("Client on socket %d disconnected\n", client_sock);
                    close(client_sock);
                    FD_CLR(client_sock, &master_fds);
                    client_socks[i] = 0;
                } else {
                    // 클라이언트로부터 데이터를 받음
                    buffer[bytes_received] = '\0';
                    printf("Received from socket %d: %s", client_sock, buffer);

                    // 모든 클라이언트에게 메시지 전송
                    for (int j = 0; j < max_clients; ++j) {
                        int dest_sock = client_socks[j];
                        if (FD_ISSET(dest_sock, &master_fds) && dest_sock != server_sock && dest_sock != client_sock) {
                            send(dest_sock, buffer, bytes_received, 0);
                        }
                    }
                }
            }
        }
    }

    return 0;
}
