#include<stdio.h>
#include<fcntl.h>
#include<signal.h>
#include<unistd.h>
#include<string.h>

int main()
{
	char arg[4]=">>";
	int pid;
	//execl("/bin/ls","ls","-a","/",NULL);
	//wait(NULL);
	int fd = open("data",O_RDWR);
	if(write(fd,arg,strlen(arg))==-1)
		printf("write error");
	if((pid=fork())!=0)
		perror("fork");
	else{
			if(pid==0)
			{
				execl("/bin/who","who",">","data",NULL);
				exit(17);
			}
			else
			{
				wait(NULL);
				close(fd);
			}
	}
	return 0;
}
