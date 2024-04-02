#include<stdio.h>
#define size 5

int queue[size],front=-1,rear=-1;

void enqueue()
{
	int x;
	if(rear == size-1)
		printf("Queue is overflow\n");
	else if(front == -1 && rear == -1)
	{
		front=rear=0;
		printf("Enter data: ");
		scanf("%d",&x);
		queue[rear]=x;
	}
	else
	{
		printf("Enter data: ");
		scanf("%d",&x);
		rear++;
		queue[rear]=x;
	}
	
}

void dequeue()
{
	if(front == -1 && rear == -1)
		printf("Queue is empty\n");
	else if(front == rear)
		front = rear =-1;
	else
	{
		printf("Dequeued data is %d\n",queue[front]);
		front++;
	}
}

void peek()
{
	if(front == -1 && rear == -1)
		printf("Queue is empty\n");
	else
		printf("peek data is %d\n",queue[front]);
}

void display()
{
	if(front == -1 && rear == -1)
		printf("Queue is empty\n");
	else
	{
		for(int i=front;i<rear+1;i++)
			printf("%d ",queue[i]);
	}
}

int main()
{
	int option;
	while(1)
	{
		printf("\n1 -> enqueue\n");
		printf("2 -> dequeue\n");
		printf("3 -> peek\n");
		printf("4 -> display\n");
		printf("5 -> exit\n\n");
		printf("Choose an option: ");
		scanf("%d",&option);
		switch(option)
		{
			case 1: enqueue();break;
			case 2: dequeue();break;
			case 3: peek();break;
			case 4: display();break;
			case 5: return 0;
			default:printf("Choose correct option\n");
		}
	}
	
}

