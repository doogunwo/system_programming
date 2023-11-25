#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void alarm_handler(int);

int alarm_flag = 0;

int main() {
    struct sigaction act;
    act.sa_handler = alarm_handler;
    sigaction(SIGALRM, &act, NULL);

    alarm(5);
    pause();

    if (alarm_flag) {
        printf("Passed 5 seconds.\n");
    }

    return 0;
}

void alarm_handler(int sig) {
    printf("Alarm signal\n");
    alarm_flag = 1;
}
