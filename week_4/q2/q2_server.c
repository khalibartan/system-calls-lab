#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#define FIFO_S "/tmp/fifo.server"

int main(){
    printf("Client will send output of ls -l, and server will sort it");
    unlink(FIFO_S);
    mkfifo(FIFO_S, 0600);
    int server = open(FIFO_S, O_RDONLY);
    close(0);
    dup(server);
    execlp("sort","sort",NULL);
    return 0;
}
