#include<stdio.h>
#define size 5
int stack[size],top=-1;

void push()
{
	int x;
	printf("Enter data: ");
	scanf("%d",&x);
	if(top == size-1)
		printf("Stack is overflow\n\n");
	else
	{
		top++;
		stack[top]=x;
	}
}

void pop()
{
	int x;
	if(top == -1)
		printf("Stack is underflow\n\n");
	else
	{
		x=stack[top];
		top--;
		printf("Pop data : %d\n\n",x);
	}
}

void peek()
{
	if(top == -1)
		printf("Stack is empty\n\n");
	else
		printf("%d\n\n",stack[top]);
}

void display()
{
	for(int i=top;i>=0;i--)
		printf("%d \n",stack[i]);
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
