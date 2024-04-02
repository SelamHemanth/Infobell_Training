#include<stdio.h>
#include<stdlib.h>

struct node
{
	int data;
	struct node *next;
};
struct node *top;
void push()
{
	int x;
	struct node *new;
	new=(struct node *)malloc(sizeof(struct node));
	printf("Enter data: ");
	scanf("%d",&x);
	new->data=x;
	new->next=top;
	top=new;
}

void pop()
{
struct node *temp=top;
if(top == 0)
	printf("Stack is empty\n");
else
{
	printf("Poped element is %d\n",top->data);
	top=top->next;
	free(temp);
}
}

void peek()
{
	if(top == 0)
		printf("Stack is empty\n");
	else
		printf("Top data is %d\n",top->data);
}

void display()
{
struct node *temp=top;
if(top == 0)
	printf("Stack is empty\n");
while(temp != 0)
{
	printf("%d ",temp->data);
	temp=temp->next;
}
}

int main()
{
	int option;
	while(1)
	{
		printf("\n1 -> push\n");
		printf("2 -> pop\n");
		printf("3 -> peek\n");
		printf("4 -> display\n");
		printf("5 -> exit\n\n");
		printf("Choose an option: ");
		scanf("%d",&option);
		switch(option)
		{
			case 1: push();break;
			case 2: pop();break;
			case 3: peek();break;
			case 4: display();break;
			case 5: return 0;
			default:printf("Choose correct option\n");
		}
	}
	
}

