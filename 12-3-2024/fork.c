#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	 pid_t n;
	if((n=fork())>=0)
	{
		printf("Child ID %d\n",getpid());
		exit(0);
	}
	wait(0);
	printf("Hello\n");
	printf("Parent ID %d\n",getpid());
}
