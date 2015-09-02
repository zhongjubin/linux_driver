#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

void main(int ac, char* av[])
{
	int pid,fd;
	if(ac!=2)
		exit(0);
	fd = open(av[1],O_RDWR | O_CREAT, 0744);
	if((pid=fork())<0)
		exit(1);
	if(pid==0)
	{
		dup2(fd,0);
		close(fd);
		execlp("sort","sort",NULL);
		exit(2);
	}

	wait(NULL);
	exit(0);
}
