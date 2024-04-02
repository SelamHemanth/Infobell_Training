#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
int main()
{
	ssize_t  size;
	size=write(0,"hello world\n",13);
	if(size<0 || size != 13)
	{
		fprintf(stderr,"write system call failed\n");
		exit(1);
	}
	exit(0);
}
