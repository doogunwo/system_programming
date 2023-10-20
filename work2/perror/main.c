#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


void my_perror(const char *s){
    if(s !=NULL){
        fprintf(stderr, "%s: %s\n",s,strerror(errno));
    }
    else{
        fprintf(stderr, "%s\n",strerror(errno));
    }
}

int main(int argc, char *argv[]){
    FILE *f;

    if(argc < 2) {
        printf("Usage: strerror_show nofilename\n");
        exit(1);
    }

    if((f=fopen(argv[1],"r"))==NULL){
        printf("Cannot open a file \"%s\"... (error message: %s)\n",argv[1], strerror(errno));
        my_perror("Cannot open a file");
        exit(1);
    }

    printf("Open a file \"%s\".\n", argv[1]);
    fclose(f);


}

