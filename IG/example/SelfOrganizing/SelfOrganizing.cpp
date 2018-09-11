#include<iostream>
 
using namespace std;
 
// A structure to representing a node.
struct node
{
	int data;
	node *next;
};
 
// A function to create a new node.
node* CreateNode(int data)
{
	node *newnode = new node;
	newnode->data = data;
	newnode->next = NULL;
	return newnode;
}
 
// A function to add the data at the end of the list.
node* InsertIntoList(node *head, int data)
{
	node *temp = CreateNode(data);
	node *t = new node;
	t = head;
	if(head == NULL)
	{
		head = temp;
		return head;
	}
	else
	{
		// Traversing to the end of the list.
		while(t->next != NULL)
			t = t->next;
		// Add the node at the end. 
		t->next = temp;
	}
	return head;
}
 
void Display(node *head)
{
	node *temp = new node;
	temp = head;
	cout<<"\n The list state is :";
	// Display the list.
	while(temp->next != NULL)
	{
		cout<<"->"<<temp->data;
		temp = temp->next;
	}
}
 
node* SearchItem(node *head, int item)
{
	int flag = 0;
	node *temp = new node;
	node *t = new node;
	temp = head;
	if(temp->data == item)
	{
		cout<<"\nItem found at head node";
		flag = 5;
		Display(head);
		return head;
	}
	else
	{
		while((temp->next)->next != NULL)
		{
			if((temp->next)->data == item)
			{
				cout<<"\n item found";
				flag = 5;
				break;
			}
			temp = temp->next;
		}
		// Organising the list.
		// Shifting the searched node to the head.
		t = (temp->next)->next;
		(temp->next)->next = head;
		head = temp->next;
		temp->next = t;
		if(flag == 5)
			Display(head);
		else
			cout<<"\nItem not found.";
	}
	return head;
}
 
int main()
{
	int i, n;
	char ch;
	node *head = new node;
	head = NULL;
 
	for(i = 1; i < 11; i++)
		head = InsertIntoList(head, i);
 
	Display(head);
 
	up:
	cout<<"\nEnter the Element to be searched: ";
	cin>>n;
	// Update the head of the list.
	head = SearchItem(head, n);
 
	cout<<"\n\n\tDo you want to search more...enter choice(y/n)?";
	cin>>ch;
	if(ch == 'y' || ch == 'Y')
	goto up;
 
	return 0;
}