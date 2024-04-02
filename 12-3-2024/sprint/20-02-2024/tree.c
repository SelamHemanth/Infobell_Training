#include <stdio.h>
#include <stdlib.h>
 
typedef struct node
{
        struct node *left;
        int data;
        struct node *right;
}Node;
 
int insert_BST(Node **root, int data)
{
        Node *new = malloc(sizeof(Node));
        if(new == NULL)
        {
                return 0;
        }
 
        new -> data = data;
        new -> left = NULL;
        new -> right = NULL;
 
        if(*root == NULL)
        {
                *root = new;
                return 1;
        }
 
        Node *temp = *root, *parent = NULL;
        int flag = 0;
        while(temp)
        {
                parent = temp;
		if(data == temp -> data)
		{
			printf("Duplicating elements are not allowes in trees!\n");
			return 0;
		}
                if(data < temp -> data)
                {
                        temp = temp -> left;
                        flag = 1;
                }
                else if(data > temp -> data)
                {
                        temp = temp -> right;
                        flag = 0;
                }
        }
        if(flag)
        {
                parent -> left = new;
        }
        else
        {
                parent -> right = new;
        }
}
 
int inorder(Node *root)
{
        if(root != NULL)
        {
		printf("In order: ");
                inorder(root -> left);
                printf("%d ", root -> data);
                inorder(root -> right);
        }
	printf("\n");
}
 
int preorder(Node *root)
{
        if(root != NULL)
        {
		printf("Pre order: ");
                printf("%d ", root -> data);
                preorder(root -> left);
                preorder(root -> right);
        }
	printf("\n");
}
 
int postorder(Node *root)
{
        if(root != NULL)
        {
		printf("Post order: ");
                postorder(root -> left);
                postorder(root -> right);
                printf("%d ", root -> data);
        }
	printf("\n");
}
 
int find_max(Node *root)
{
        while(root -> right != NULL)
        {
                root = root -> right;
        }
        printf("maximum Value is %d ", root -> data);
}
 
int find_min(Node *root)
{
        while(root -> left != NULL)
        {
                root = root -> left;
        }
        printf("Minimum Value is %d ", root -> data);
}
 
int search_element(Node *root, int data)
{
        Node *temp = root;
        while(temp)
        {
                if(data < temp -> data)
                {
                        temp = temp -> left;
                }
                else if(data > temp -> data)
                {
                        temp = temp -> right;
                }
                else
                {
                        return temp -> data;
                }
        }
        return 0;
}
 
int main()
{
        Node *root = NULL;
        int option, data;
        while(1)
        {
                printf("\n1.Insert\n2.In-order\n3.Pre-order\n4.Post-order\n5.Find-max\n6.Find-min\n7.Search element\n8.Exit\n");
                scanf("%d", &option);
                switch(option)
                {
                        case 1:
                                printf("Enter the data to be inserted : ");
                                scanf("%d", &data);
                                insert_BST(&root, data);
                                break;
                        case 2:
                                inorder(root);
                                break;
                        case 3:
                                preorder(root);
                                break;
                        case 4:
                                postorder(root);
                                break;
                        case 5:
                                find_max(root);
                                break;
                        case 6:
                                find_min(root);
                                break;
                        case 8:
                                return 0;
                        case 7:
                                printf("Enter the element to be searched : ");
                                scanf("%d", &data);
                                if(search_element(root, data))
                                {
                                        printf("ELement found\n");
                                }
                                else
                                {
                                        printf("Element not found\n");
                                }
                                break;
                }
        }
}
