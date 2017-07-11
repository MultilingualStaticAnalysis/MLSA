/*
* C Program to Find the Summation of Node values at level/row and print it
*/
#include <stdio.h>
#include <stdlib.h>
 
struct btnode
{
    int value;
    struct btnode *r,*l;
}*root = NULL, *temp = NULL;
 
void create();
void insert();
void add(struct btnode *t);
void computesum(struct btnode *t);
void display();
 
int count = 0, sum[100] = {0}, max = 0;
 
void main()
{
    int ch;
 
    printf("\n OPERATIONS ---");
    printf("\n 1] Insert an element into tree");
    printf("\n 2] Display the sum of the elements at the same level");
    printf("\n 3] Exit ");    
    while (1)
    {                        
        printf("\nEnter your choice : ");
        scanf("%d", &ch);
        switch (ch)
        {
        case 1:    
            insert();
            break;
        case 2: 
            count = 0;
            max = 0;
            computesum(root);
            display();
            break;
        case 3: 
            exit(0);
        default :     
            printf("Wrong choice, Please enter correct choice  ");
            break;    
        }
    }
}
 
/* To create a new node with the data from the user */
void create()
{
    int data;
 
    printf("Enter the data of node : ");
    scanf("%d", &data);
    temp = (struct btnode* ) malloc(1*(sizeof(struct btnode)));
    temp->value = data;
    temp->l = temp->r = NULL;
}
 
/* To check for root node and then create it */
void insert()
{
    create();
 
    if (root == NULL)
        root = temp;
    else
        add(root);
}
 
/* Search for the appropriate position to insert the new node */
void add(struct btnode *t)
{
    if ((temp->value > t->value) && (t->r != NULL))        /* value more than root node value insert at right */
        add(t->r);
    else if ((temp->value > t->value) && (t->r == NULL))        
        t->r = temp;
    else if ((temp->value < t->value) && (t->l != NULL))        /* value less than root node value insert at left */
        add(t->l);
    else if ((temp->value < t->value) && (t->l==NULL))
        t->l = temp;
}
 
/* Function to find the sum of nodes at same distance */
void computesum(struct btnode *t)
{
    if (root == NULL)
    {    
        printf("Tree is empty ");
        return;
    }
    if (t->l != NULL)
    {
        count++;    
        computesum(t->l);
    }
    sum[count] = sum[count] + t->value;  /* addition of elelment by row wise */
    if (max < count)
        max = count;
    if (t->r != NULL)
    {
        count++;        
        computesum(t->r);
    }
    count--;
}
 
/* To display the sum of the nodes at the same distance */
void display()
{
    int i;
 
    printf("Sum of nodes : \n Level \t Sum ");
    for (i = 0; i <= max; i++)
       printf("\n %d \t: %d ", i, sum[i]);
}