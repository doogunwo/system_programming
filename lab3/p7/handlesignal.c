#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void handler(int signo);

int main() {
    struct sigaction act;
    int i = 0;

    act.sa_handler = handler;
    sigfillset(&(act.sa_mask)); // sigfileset 대신 sigfillset을 사용
    sigaction(SIGINT, &act, NULL);

    printf("SIGINT on\n");

    while (1) {
        sleep(1);
        printf("sleep for %d sec(s).\n", ++i);
    }

    return 0;
}

void handler(int signo) {
    printf("handle: signo=%d\n", signo);
}
