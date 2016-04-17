#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#define FIFO_S "/tmp/fifo.server"

int main(){
    int server = open(FIFO_S,O_WRONLY);
    close(1);
    dup(server);
    execlp("ls","ls","-l",NULL);
    close(server);
    return 0;

}
