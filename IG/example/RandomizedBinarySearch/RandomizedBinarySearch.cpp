/*
 *  C++ Program to Implement Randomized Binary Search Tree
 */
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <cstdlib>   
#define MAX_VALUE 65536
using namespace std;
/*
 * Class RBSTNode 
 */
class RBSTNode
{  
    public: 
        RBSTNode *left, *right;
        int priority, element;  
        /* Constructor */
        RBSTNode()
        {
            this->element = 0;
            this->left = this;
            this->right = this;
            this->priority = MAX_VALUE;         
        }    
         /* Constructor */    
        RBSTNode(int ele)
        {
            RBSTNode(ele, NULL, NULL);         
        } 
        /* Constructor */
        RBSTNode(int ele, RBSTNode *left, RBSTNode *right)         
        {
            this->element = ele;
            this->left = left;
            this->right = right;
            this->priority = rand() % 100 + 1;
        }    
};
 
/*
 * Class RandomizedBinarySearchTree 
 */
class RandomizedBinarySearchTree
{
    private: 
        RBSTNode *root;
        RBSTNode *nil;
    public:
        /* Constructor */
         RandomizedBinarySearchTree()
         {
             root = nil;
         }
         /* Function to check if tree is empty */
         bool isEmpty()
         {
             return root == nil;
         }
         /* Make the tree logically empty **/
         void makeEmpty()
         {
             root = nil;
         }
 
         /* Functions to insert data **/
         void insert(int X)
         {
             root = insert(X, root);
         }
         RBSTNode *insert(int X, RBSTNode *T)\
         {
             if (T == nil)
                 return new RBSTNode(X, nil, nil);
             else if (X < T->element)
             {
                 T->left = insert(X, T->left);
                 if (T->left->priority < T->priority)
                 {
                      RBSTNode *L = T->left;
                      T->left = L->right;
                      L->right = T;
                      return L;
                  }    
             }
             else if (X > T->element)
             {
                 T->right = insert(X, T->right);
                 if (T->right->priority < T->priority)
                 {
                     RBSTNode *R = T->right;
                     T->right = R->left;
                     R->left = T;
                     return R;
                 }
             }
             return T;
         }
         /*
          * Functions to count number of nodes 
          */
         int countNodes()
         {
             return countNodes(root);
         }
 
         int countNodes(RBSTNode *r)
         {
             if (r == nil)
                 return 0;
             else
             {
                 int l = 1;
                 l += countNodes(r->left);
                 l += countNodes(r->right);
                 return l;
             }
         }
         /*
          * Functions to search for an element 
          */
         bool search(int val)
         {
             return search(root, val);
         }
         bool search(RBSTNode *r, int val)
         {
             bool found = false;
             while ((r != nil) && !found)
             {
                 int rval = r->element;
                 if (val < rval)
                     r = r->left;
                 else if (val > rval)
                     r = r->right;
                 else
                 {
                     found = true;
                     break;
                 }
                 found = search(r, val);
             }
             return found;
         }
 
         /*
          * Function for inorder traversal 
          */
         void inorder()
         {
             inorder(root);
         }
 
         void inorder(RBSTNode *r)
         {
             if (r != nil)
             {
                 inorder(r->left);
                 cout<<r->element <<"  ";
                 inorder(r->right);
             }
         }
         /*
          * Function for preorder traversal 
          */
         void preorder()
         {
             preorder(root);
         }
         void preorder(RBSTNode *r)
         {
             if (r != nil)
             {
                 cout<<r->element <<"  ";
                 preorder(r->left);             
                 preorder(r->right);
             }
         }
 
         /*
          * Function for postorder traversal 
          */
         void postorder()
         {
             postorder(root);
         }
         void postorder(RBSTNode *r)
         {
             if (r != nil)
             {
                 postorder(r->left);             
                 postorder(r->right);
                 cout<<r->element <<"  ";
             }
         }         
};     
 
/*
 * Main Contains Menu 
 */
 
int main()
{            
    RandomizedBinarySearchTree rbst; 
    cout<<"Randomized Binary SearchTree Test\n";          
    char ch;
    int choice, item;
    /*
     * Perform tree operations  
     */
    do    
    {
        cout<<"\nRandomized Binary SearchTree Operations\n";
        cout<<"1. Insert "<<endl;
        cout<<"2. Search "<<endl;
        cout<<"3. Count Nodes "<<endl;
        cout<<"4. Check Empty"<<endl;
        cout<<"5. Clear"<<endl;
        cout<<"Enter your choice: ";
        cin>>choice;            
        switch (choice)
        {
        case 1: 
            cout<<"Enter integer element to insert: ";
            cin>>item;
            rbst.insert(item);                     
            break;                          
        case 2: 
            cout<<"Enter integer element to search: ";
            cin>>item;
            if (rbst.search(item))
                cout<<"Element "<<item<<" found in the Tree"<<endl;
            else
                cout<<"Element "<<item<<" not found in the Tree"<<endl;
            break;                                          
        case 3: 
            cout<<"Nodes = "<<rbst.countNodes()<<endl;
            break;     
        case 4:
            if (rbst.isEmpty()) 
                cout<<"Tree is Empty"<<endl;
            else
                cout<<"Tree is not Empty"<<endl;
            break;
        case 5: 
            cout<<"\nRandomizedBinarySearchTree Cleared"<<endl;
            rbst.makeEmpty();
            break;            
        default: 
            cout<<"Wrong Entry \n ";
            break;   
        }
 
        /**  Display tree  **/ 
        cout<<"\nPost order : ";
        rbst.postorder();
        cout<<"\nPre order : ";
        rbst.preorder();    
        cout<<"\nIn order : ";
        rbst.inorder();
        cout<<"\nDo you want to continue (Type y or n) \n";
        cin>>ch;                  
    } 
    while (ch == 'Y'|| ch == 'y');               
    return 0;
}