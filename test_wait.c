#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void main(int ac, char* av[])
{
	int pid;
	int thepipe[2];
	//pipe(thepipe);
	if((pid=fork())<0)
		perror("cannot fork");

	if(pid==0)
	{
		//close(thepipe[1]);
		//dup2(thepipe[0],0);
		//close(thepipe[0]);
		execlp("sort","sort",NULL);
		exit(1);
	}
	if(pid>0)
	{
		//close(thepipe[0]);
		//close(thepipe[1]);
		wait(NULL);
		printf("sort end");
	}
	exit(0);
}
