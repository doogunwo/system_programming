#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#define PORT 8050
#define MAX_REQUEST_SIZE 8192


void handle_request(int client_socket){
    char buffer[1024];
    ssize_t bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);
    if (bytes_received < 0) {
        perror("recv");
        return;
    }

    char method[10], path[256];
    sscanf(buffer, "%s %s", method, path);
    if (strcmp(method, "GET") == 0){
        char response[MAX_REQUEST_SIZE];
        sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
        sprintf(response + strlen(response), "<html><body><h1>GET Request</h1><p>%s</p></body></html>\r\n", path);
        send(client_socket, response, strlen(response), 0);
    }
    else if (strcmp(method, "POST") == 0){
        char response[MAX_REQUEST_SIZE];
        sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n");
        sprintf(response + strlen(response), "<html><body><h1>POST Request</h1><p>%s</p></body></html>\r\n", path);
        send(client_socket, response, strlen(response), 0);

    }
}

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_addr_len = sizeof(client_addr);

    // 소켓 생성
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // 서버 주소 설정
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 소켓과 주소를 바인드
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("Socket bind failed");
        exit(EXIT_FAILURE);
    }

    // 연결 대기열 설정
    if (listen(server_socket, 5) == -1) {
        perror("Listen failed");
        exit(EXIT_FAILURE);
    }

     printf("Server is listening on http://127.0.0.1:%d\n", PORT);

    // 클라이언트 연결 수락
    if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_addr_len)) == -1) {
        perror("Accept failed");
        exit(EXIT_FAILURE);
    }

    // 클라이언트 요청을 처리
    while (1) {
        int client_socket = accept(server_socket, NULL, NULL);
        if (client_socket < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }

        handle_request(client_socket);
    }

    close(server_socket);

    return 0;
}
