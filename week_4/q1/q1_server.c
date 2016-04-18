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
    FILE *ser = fdopen(server, "r");
    char client_path[1000];
    fscanf(ser, "%s",client_path);
    printf("lol");
    char buff[1000];
    printf("This is server, enter a message to send: ");
    scanf("%s",buff);
    int client = open(client_path, O_WRONLY);
    FILE *cli = fdopen(client, "w");
    fprintf(cli,"%s",buff);
    fclose(cli);
    close(server);
    close(client);
    getchar();
    return 0;
}
