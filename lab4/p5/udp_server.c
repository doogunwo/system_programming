#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <unistd.h>
#define PORT 5000 /* 서버 포트 */
#define BACKLOG 10
#define MAXBUF 100

int main() {
    int sock;
    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    int clnt_addr_len;
    char buf[MAXBUF];
    int sin_size;
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        perror("socket");
        exit(1);
    }
    /* 서버 포트 설정 */
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sock, (struct sockaddr *) &serv_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        close(sock);  // bind 실패 시 소켓 닫기
        exit(1);
    }
    while (1) {
        clnt_addr_len = sizeof(clnt_addr);
        memset(buf, 0, MAXBUF);

        if (recvfrom(sock, buf, MAXBUF, 0, (struct sockaddr *) &clnt_addr, &clnt_addr_len) == -1) {
            perror("recv");
            exit(0);
        }

        buf[MAXBUF - 1] = '\0';  // NULL 문자 추가
        printf("server: got connection from %s\n", inet_ntoa(clnt_addr.sin_addr));

        /* 메시지 송신 */
        if (sendto(sock, buf, strlen(buf), 0, (struct sockaddr *) &clnt_addr, sizeof(clnt_addr)) == -1) {
            perror("send");
            close(sock);
            exit(0);
        }
    }

    return 0;
}
