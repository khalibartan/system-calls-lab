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
    FILE *ser = fdopen(server, "w");
    fprintf(ser,"%s",path);
    fclose(ser);
    printf("%d",pid);
    mkfifo(path, 0600);
    int client  = open(path, O_RDONLY);
    FILE *cli = fdopen(client, "r");
    char buff[1000];
    fscanf(cli,"%s",buff);
    fclose(cli);
    printf("This is client , got message: %s\n",buff);
    close(server);
    close(client);
    getchar();
    return 0;

}
