//Write a multithread code to print n number of prime numbers
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


void *thread_function(void);

void prime_function()
{
	int number=0;
	printf("Enter number: ");
	scanf("%d",&number);
	for(int n=1;n<number;n++)
	{
		int i=1,count=0;
		do
		{
			if (n% i == 0)
				count++;
			i++;
		}while(i<=n);
		if(count<=2)
			printf("%d ", n);
	}
}

int main()
{
	int ret;
	pthread_t thread;
	void *return_value;

	ret = pthread_create(&thread,NULL,thread_function,(void *)NULL);
	if (ret < 0){
		perror("pthread_1 create fail:");
		exit(0);
	}
	ret = pthread_join(thread,&return_value);
	if (ret < 0){
		perror("pthread join fail:");
		exit(0);
	}
	printf("%s",(char *)return_value);
	printf("\nMain thread exited.\n");
	return 0;
}

void *thread_function()
{
	prime_function();
	pthread_exit("\nThread completed successfully\n");	
}

