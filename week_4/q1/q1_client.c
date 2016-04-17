#include<stdio.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
#define FIFO_S "/tmp/fifo.server"

int main(){
    char path[100] = "fifo.";
    pid_t pid = getpid();
    char id[100];
    sprintf(id, "%d", pid);
    strcat(path, id);
    int server = open(FIFO_S, O_WRONLY);
    write(server, path, sizeof(char)*strlen(path));
    mkfifo(path, 0600);
    int client  = open(path, O_RDONLY);
    char buff[1000];
    read(client, buff, sizeof(buff));
    printf("This is client , got message: %s\n",buff);
    close(server);
    close(client);
    getchar();
    return 0;

}
