#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/epoll.h>

#define MAX_EVENTS 10
#define PORT 12345
#define BUFFER_SIZE 1024

int main() {
    int server_socket, client_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    struct epoll_event event, events[MAX_EVENTS];
    int epoll_fd, num_ready;

    // 서버 소켓 생성
    if ((server_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket 생성 오류");
        exit(EXIT_FAILURE);
    }

    // 서버 주소 설정
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // 서버 소켓에 주소 바인딩
    if (bind(server_socket, (struct sockaddr *)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind 오류");
        exit(EXIT_FAILURE);
    }

    // 클라이언트의 연결 대기
    if (listen(server_socket, 5) == -1) {
        perror("listen 오류");
        exit(EXIT_FAILURE);
    }

    // epoll 생성
    if ((epoll_fd = epoll_create1(0)) == -1) {
        perror("epoll 생성 오류");
        exit(EXIT_FAILURE);
    }

    // 서버 소켓을 epoll에 등록
    event.events = EPOLLIN;
    event.data.fd = server_socket;
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, server_socket, &event) == -1) {
        perror("epoll_ctl 오류");
        exit(EXIT_FAILURE);
    }

    printf("에코 서버가 시작되었습니다. 클라이언트의 연결을 기다립니다...\n");

    while (1) {
        // epoll 대기
        if ((num_ready = epoll_wait(epoll_fd, events, MAX_EVENTS, -1)) == -1) {
            perror("epoll_wait 오류");
            exit(EXIT_FAILURE);
        }

        for (int i = 0; i < num_ready; i++) {
            if (events[i].data.fd == server_socket) {
                // 새로운 클라이언트의 연결이 있을 경우
                if ((client_socket = accept(server_socket, (struct sockaddr *)&client_addr, &client_len)) == -1) {
                    perror("accept 오류");
                    exit(EXIT_FAILURE);
                }

                // 클라이언트 소켓을 epoll에 등록
                event.events = EPOLLIN | EPOLLET;
                event.data.fd = client_socket;
                if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_socket, &event) == -1) {
                    perror("epoll_ctl 오류");
                    exit(EXIT_FAILURE);
                }

                printf("클라이언트가 연결되었습니다. (소켓: %d)\n", client_socket);
            } else {
                // 기존 클라이언트로부터 메시지 수신 및 에코
                char buffer[BUFFER_SIZE];
                ssize_t bytes_received = recv(events[i].data.fd, buffer, sizeof(buffer), 0);
                if (bytes_received <= 0) {
                    // 클라이언트가 연결을 끊은 경우
                    printf("클라이언트가 연결을 끊었습니다. (소켓: %d)\n", events[i].data.fd);
                    epoll_ctl(epoll_fd, EPOLL_CTL_DEL, events[i].data.fd, NULL);
                    close(events[i].data.fd);
                } else {
                    // 수신한 메시지를 클라이언트에게 에코
                    send(events[i].data.fd, buffer, bytes_received, 0);
                }
            }
        }
    }

    // 서버 소켓 닫기
    close(server_socket);

    return 0;
}
