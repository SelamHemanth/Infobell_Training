#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
	int fd;
	if((fd=open("/home/amd/hemanth/training/test.txt",O_WRONLY))<0)
		printf("File not opened\n");
	else
	{
		int a=fork();
		if(a>0)
		{
			for(int i=0;i<10000;i++)
				write(fd,"C",0);
		}
		else
			for(int i=0;i<10000;i++)
                                write(fd,"P",0);
	}
	exit(0);
}
