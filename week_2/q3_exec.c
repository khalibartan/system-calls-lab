#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<stdlib.h>
int main()
{
  pid_t pid = fork();
  int exit_status = 1;
  char *argv[]={"/bin/ls","-l","-R","/etc",0};
  if(pid == -1){
      pid = fork();
  }
  else if(pid == 0){
      pid = getpid();
      printf("Child process with process id %d\n",getpid());
      execv(argv[0],argv);
      exit(exit_status);
  }
  else{
      printf("This parent process with process id : %d\n",getpid());
      wait(&exit_status);
      if(WIFSIGNALED(exit_status)){
          printf("Execution was stopped using signal %d\n",WTERMSIG(exit_status));
      }
    }
  return 0;
}
