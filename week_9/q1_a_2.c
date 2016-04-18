#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/wait.h>

#define FIFO1 "/tmp/fifo.1"
#define FIFO2 "/tmp/fifo.2"
#define PERM 0666

int totalDistance=100,t_pos=0,h_pos=0,f=1,gap=20,flag=1;

void turtle(){
		t_pos += 1;	
	if(t_pos>=totalDistance)
	{
		printf("Turtle win\n");
		f=0;
	}
}

void hare(){
	if(h_pos-t_pos<gap && flag)
		h_pos+=5;
	else
		flag=0;
	if(!flag && t_pos-h_pos>gap){
		h_pos+=5;
		flag=1;
	}
	if(h_pos>=totalDistance){
		printf("Hare win\n");
		f=0;
	}	
}

void god(){
	printf("Turtle move to %d and hare move to %d\n",t_pos,h_pos);	
}

void report(){
		printf("Hare: %d / %d\n",h_pos,totalDistance);
		printf("Turtle: %d / %d\n",t_pos,totalDistance);
}
main(){
	pid_t pid;
	int readcfd,writecfd,readpfd,writepfd;
	if(mkfifo(FIFO1,PERM)<0 && errno!=EEXIST)
		printf("fbc");
	if(mkfifo(FIFO2,PERM)<0 && errno!=EEXIST)
		printf("dvs");
	int rem,temp,i,num,n,t,h;
	pid=fork();
	
	if(pid){
		while(f){
			i=0,num=0;
			hare();
			writepfd=open(FIFO1,O_WRONLY);
			write(writepfd,&h_pos,sizeof(h_pos));
			close(writepfd);
			readpfd=open(FIFO2,O_RDONLY);
			n=read(readpfd,&t,100);	
			t_pos=t;
			close(readpfd);		
			if(t_pos>=totalDistance || h_pos>=totalDistance)
				f=0;	
		}	
		wait(NULL);
	}
	else{
		while(f){
			turtle();		
			temp=t_pos;
			readcfd=open(FIFO1,O_RDONLY);			
			n=read(readcfd,&h,100);
			h_pos=h;
			close(readcfd);
			writecfd=open(FIFO2,O_WRONLY);
			write(writecfd,&t_pos,sizeof(t_pos));
			report();
			god();
			close(writecfd);
			if(t_pos>=totalDistance || h_pos>=totalDistance)
				f=0;
		}
	}	
}
