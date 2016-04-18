#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<signal.h>
#define N 100

int pid[N],fd[N][2],win,n,tok,tok1,pt[N],p;
char a[1000];
void player(int);

int main(int argc, char *argv[])
{
    printf("\nEnter No. of Players : ");
    scanf("%d",&n);
    printf("\nEnter Token Value : ");
    scanf("%d",&tok);
    tok1=tok;
    printf("Enter the winning score:\n");
    scanf("%d", &win);
    int i;
    for(i=0;i<n;i++)
    {
	 pt[i]=0;
    }
   for(i=0;i<n;i++)
    {
    p=fork();
    pipe(fd[i]);
    if(!p)
    {
               pid[i]=(int)getpid();
    }
    else
     {
       exit(0);
     }
} 
int d=tok,j=0;
while(d>0)
{
  a[j++]=d%10+48;
  d/=10;
}
    a[j]='\0';
    write(fd[0][1],a,sizeof(a));
    player(0);   
    return 0;
 }

void player(int i)
{
   int token=0,next;
   read(fd[i][0],a,sizeof(a));
   int j;
for(j=strlen(a)-1;j>=0;j--)
{
  token=token*10+a[j]-48;
}
  if(i==n-1)
     next=0;
  else
    next=i+1;
    printf("\nPlayer number =%d,have received a token with value %d and sending token to player %d",i+1,token,next);
    int k;
    token--;
    if(token==0)
     {
      pt[i]++;
      token=tok;
    }
      if(pt[i]==win)
        {
        printf("\nI am player number %d. I have %d points. I have won!!!",i,pt[i]);
        for(k=0;k<n;k++)
        {          if(k!=i)
        {
           kill(pid[i],SIGTERM);
           printf("I am player number %d. I have been killed.\n",k);      
        }}
        exit(1);
        }
  else
  {
  int d=token;
  j=0;
  while(d>0)
  {
  a[j++]=d%10+48;
  d/=10;
   }
      write(fd[next][1],a,sizeof(a));
      printf(" My current points are %d",pt[i]);
      player(next);
      }
}
  
