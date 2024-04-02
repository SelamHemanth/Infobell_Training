#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
int main()
{
	pid_t pid,child;
	pid=fork();
	if(pid>0)
	{
		printf("child-1 -> %d\n",getpid());
	}
	else
	{
	child=fork();
        if(child>0)
             printf("Child-2 -> %d\n",getpid());
	else
	printf("Parent -> %d\n",getpid());
	}
	exit(0);
}
