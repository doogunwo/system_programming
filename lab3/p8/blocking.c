#include <fcntl.h>
#include <errno.h>

#define MSGSIZE 16

char *parent_name = "parent";
char *child_name = "child";
char *parent_msg = "Hello, child!";
char *child_msg = "Hello, parent";

void nonblock_rw(char *, int,int,char *);

int main(){
    int pp[2][2],i;
    int pid;

    for ( i = 0; i<2; i++){
        if(pipe(pp[i]==-1)){
            perror("pipe call failed");
            exit(1);
        }
    }

    pid = fork();
    if(pid==0){
        close(pp[0][1]);
        close(pp[1][0]);
        nonblock_rw(child_name,pp[0][0],pp[1][1],child_msg);
    }
}