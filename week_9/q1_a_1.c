#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/wait.h>
int totalDistance=100,t_pos=0,h_pos=0,f=1,gap=20,flag=1;

void turtle()
{
	t_pos += 1;	
	if(t_pos>=totalDistance)
	{
		printf("Turtle win\n");
		f=0;
	}
}

void hare()
{
	if(h_pos-t_pos<gap && flag)
		h_pos+=5;
	else
		flag=0;
	if(!flag && t_pos-h_pos>gap)
	{
		h_pos+=5;
		flag=1;
	}
	if(h_pos>=totalDistance)
	{
		printf("Hare win\n");
		f=0;
	}	
}

void god()
{
	printf("Turtle move to %d and hare move to %d\n",t_pos,h_pos);	
}

void report()
{
		printf("Hare: %d / %d\n",h_pos,totalDistance);
		printf("Turtle: %d / %d\n",t_pos,totalDistance);
}

main()
{
	pid_t pid;
	int ptoc[2],ctop[2];
	int rem,temp,i,num,n,t,h;
	if(pipe(ptoc)<0)
		perror("pipe error");
	if(pipe(ctop)<0)
		perror("pipe error");
    pid=fork();
	
	if(pid){
		while(f){
			i=0,num=0;
			hare();
			close(ptoc[0]);
			write(ptoc[1],&h_pos,sizeof(h_pos));
			close(ctop[1]);
			n=read(ctop[0],&t,100);	
			t_pos=t;		
			if(t_pos>=totalDistance || h_pos>=totalDistance)
				f=0;	
		}	
		wait(NULL);
	}
	else{
		while(f){
			turtle();		
			temp=t_pos;
		 	close(ptoc[1]);
			n=read(ptoc[0],&h,100);
			h_pos=h;
			close(ctop[0]);
			write(ctop[1],&t_pos,sizeof(t_pos));
			report();
			god();
			if(t_pos>=totalDistance || h_pos>=totalDistance)
				f=0;
		}
	}	
}
