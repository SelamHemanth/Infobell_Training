#include <stdio.h>
#include <unistd.h>

int main()
{
	sleep(60);
	int ret=execlp("ps","ps","-l",(char*)0);
	if(ret == -1)
		perror("New process not created");
}
