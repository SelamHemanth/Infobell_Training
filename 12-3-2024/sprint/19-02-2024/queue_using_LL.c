#include<stdio.h>
#include<stdlib.h>

struct node
{
	char data;
	struct node *next;
};
struct node *front=0,*rear=0;

void enqueue()
{
	int x;
	struct node *new=(struct node *)malloc(sizeof(struct node));
	printf("Enter data: ");
	scanf("%d",&x);
	new->data=x;
	new->next=0;
	if(front == 0 && rear == 0)
		front=rear=new;
	else
	{
		rear->next=new;
		rear=new;
	}
}

void dequeue()
{
	struct node *temp;
	temp=front;
	if(front == 0 && rear == 0)
		printf("Queue is empty\n");
	else
	{
		front=front->next;
		printf("%d is removed\n",temp->data);
		free(temp);
	}
}

void peek()
{
        if(front == 0 && rear == 0)
		printf("Queue is empty\n");
	else
		printf("Peek data is %d\n",front->data);
}


void display()
{
	struct node *temp=front;
	if(front == 0 && rear == 0)
		printf("Queue is empty\n");
	else
	{
		while(temp!=0)
		{
			printf("%d ",temp->data);
			temp=temp->next;
		}
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


