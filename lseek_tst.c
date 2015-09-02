#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int *argc, char * *argv)
{
    int s;
	int result,pid;
    int fd;
    fd=open("data",O_RDWR | O_CREAT | O_TRUNC, 0744);
    s=fcntl(fd,F_GETFL);
    s=s&(~O_APPEND);
    result=fcntl(fd,F_SETFL,s);
    if(result==-1)
        perror("setting O_APPEND");
    char* av[3];
	av[0]="who";
    av[1]=">>";
    av[2]="/dev/pts/2";
    if((pid=fork())<0)
    {
        perror("fork failed");
        exit(1);
    }
    if(pid==0)
	{
		close(fd);
		close(1);
		fd=open("data",O_RDWR, 0744);
		if(execvp("who",av)<0)
        	perror("execv error");
	}
	if(pid!=0)
	{
		wait(NULL);
		fd=open("data",O_RDONLY, 0744);	
		s=fcntl(fd,F_GETFL);
        if((s&O_APPEND)!=0)
			printf("Auto %d %d\n",s,O_APPEND);
		else
			printf("lseek %d %d\n",s,O_APPEND);
		close(fd);
	}
	exit(0);  
}
