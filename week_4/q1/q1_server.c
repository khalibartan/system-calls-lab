#include<stdio.h>
#include<string.h>
#include<sys/stat.h>
#include<unistd.h>
#include<fcntl.h>
#define FIFO_S "/tmp/fifo.server"

int main(){
    unlink(FIFO_S);
    mkfifo(FIFO_S, 0600);
    int server = open(FIFO_S, O_RDONLY);
    char client_path[1000];
    read(server, client_path, sizeof(client_path));
    char buff[1000];
    printf("This is server, enter a message to send: ");
    scanf("%s",buff);
    int client = open(client_path, O_WRONLY);
    write(client,buff, sizeof(char)*strlen(buff));
    close(server);
    close(client);
    getchar();
    return 0;
}
