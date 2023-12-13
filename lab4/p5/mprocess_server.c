#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <unistd.h>
#include <signal.h>

#define MYPORT 3490 /* the port users will be connecting to */
#define BACKLOG 10   /* how many pending connections queue will hold */

void sigchld_handler(int s) {
    // 자식 프로세스가 종료되면 호출되는 핸들러
    while (waitpid(-1, NULL, WNOHANG) > 0)
        ;
}

int main() {
    int sockfd, new_fd;              /* listen on sock_fd, new connection on new_fd */
    struct sockaddr_in my_addr;      /* my address information */
    struct sockaddr_in their_addr;   /* connector's address information */
    int sin_size;
    struct sigaction sa;

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }

    my_addr.sin_family = AF_INET;         /* host byte order */
    my_addr.sin_port = htons(MYPORT);     /* short, network byte order */
    my_addr.sin_addr.s_addr = INADDR_ANY; /* auto-fill with my IP */
    memset(&(my_addr.sin_zero), 0, 8);   /* zero the rest of the struct */

    if (bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) == -1) {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    sa.sa_handler = sigchld_handler; // 모든 종자 프로세스를 waitpid()로 처리
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = SA_RESTART | SA_NOCLDSTOP;
    if (sigaction(SIGCHLD, &sa, NULL) == -1) {
        perror("sigaction");
        exit(1);
    }

    printf("Server: waiting for connections...\n");

    while (1) { /* main accept() loop */
        sin_size = sizeof(struct sockaddr_in);
        if ((new_fd = accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
            perror("accept");
            continue;
        }

        printf("Server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));

        if (!fork()) { /* this is the child process */
            close(sockfd); // 자식은 리스닝 필요 없음

            if (send(new_fd, "Hello, world!\n", 14, 0) == -1) {
                perror("send");
            }

            close(new_fd);
            exit(0);
        }

        close(new_fd); /* 부모는 클라이언트 소켓 필요 없음 */
    }

    return 0;
}
