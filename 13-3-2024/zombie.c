#include<stdio.h>
#include<unistd.h>
#include <sys/types.h>
#include <stdlib.h>
int main()
{
	pid_t ret;
	printf("Parent started\n");
	sleep(1);
	printf("Parent PID is %d\n",(int)getpid());
	if((ret=fork())==-1)
	{
		perror("Fork Failed\n");
		exit(1);
	}
	else if(ret==0)
	{
		printf("Children started\n");
		sleep(1);
		printf("Children PID is %d\n",(int)getpid());
		sleep(1);
		printf("Children died\n");
	}
	else
	{
	sleep(10);
	printf("Parent died\n");
	}
	return 0;
}
