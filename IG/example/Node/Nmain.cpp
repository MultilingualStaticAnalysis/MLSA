/*                                                                                                                                                                                                          
Anne Marie Bogar                                                                                                                                                                                            
November 9, 2014                                                                                                                                                                                            
Data Structures                                                                                                                                                                                             
Node Driver File                                                                                                                                                                                            
The user enters a Student's information (first name, last name, middle initial, social security number, age), which is then added to a list.                                                                
The user enters as many Students as they want. When the user signals that they are finished, the list of Students is printed. If there are any Christines in the list, they will deleted. Then the new list\
 will be printed.                                                                                                                                                                                           
*/

#include "Node.h"
#include "Student.h"
using namespace std;
void append(Node* &n, Node* &head); //adds a Node to the list                                                                                                                                               
void display(Node* &head); //displays the entire list of Nodes                                                                                                                                              
bool deleteNode(Node* &head, string target); //deletes a Node from the list                                                                                                                                 
void end(Node* &head); //releases all dynamically allocated memory                                                                                                                                          
void createStudent(string& f, string& l, char& m, int& ssn, int& a); //initializes information to create a Student object                                                                                   

int main()
{
   Node* head = NULL;
   Node* nPtr;
   string f, l;
   int n, ssn, a;
   char ans, m;
   bool del;

   do
   {
      createStudent(f, l, m, ssn, a);
      nPtr = new Node(f, l, m, ssn, a); //creates new Node (which nPtr points to) with the Student object just created                                                                                      
      append(nPtr, head); //appends the newly created Node to the list                                                                                                                                      
      cout << "\nAdd a new student to the list? y/n: ";
      cin >> ans;
      cout << endl;
   }while(ans == 'y' || ans == 'Y'); //Nodes will be created until user does not enter y or Y                                                                                                               

   cout << "Student list:" << endl;
   display(head); //displays list                                                                                                                                                                           

   do
   {
      del = deleteNode(head, "Christine"); //deletes all Nodes with the name Christine                                                                                                                      
   }while(del); //continue to delete Nodes until there are no more Christines in the list                                                                                                                   

   cout << "After Christine has been deleted from list:" << endl;
   display(head);
   end(head);
   return 0;
}

void createStudent(string& f, string& l, char& m, int& ssn, int& a)
//initializes all variables necessary to create a Student object                                                                                                                                            
//the variables are called by reference so that they can be used in the main function                                                                                                                       
{
   cout << "Enter first name: ";
   cin >> f;
   cout << "Enter last name: ";
   cin >> l;
   cout << "Enter middle initial: ";
   cin >> m;
   cout << "Enter social security number: ";
   cin >> ssn;
   cout << "Enter age: ";
   cin >> a;
}

void append(Node* &n, Node* &head) //adds Nodes onto the list                                                                                                                                               
{
   Node* curr;
   if(head == NULL)
      head = n; //first Node added to the list                                                                                                                                                              
   else
   {
      curr = head;
      while(curr -> getNext() != NULL) //finds the last Node in the list                                                                                                                                    
         curr = curr -> getNext();
      curr -> setNext(n); //appends Node onto the end of the list                                                                                                                                           
   }
}

void display(Node* &head) //displays the Student information for each Node on the screen                                                                                                                    
{
   Node* curr = head;
   cout << endl;
   while(curr != NULL) //goes through all Nodes                                                                                                                                                             
   {
      cout << curr -> getStudent() << endl; //displays Student information
     curr = curr -> getNext(); //goes to the next Node in the list                                                                                                                                         
   }
}

void end(Node* &head) //deletes all dynamically allocated memory at the end of the program                                                                                                                  
{
   Node* curr = head;
   Node* del;
   while(curr != NULL)
   {
      del = curr;
      curr -> deleteStudent(); //releases the Student memory of the Node                                                                                                                                    
      curr = curr -> getNext();
      delete del; //releases the Node memory                                                                                                                                                                
   }
}

bool deleteNode(Node* &head, string target) //deletes a Node in the list based on the name passed. Returns whether a Node was deleted or not                                                                
{
   bool del = false;
   Node* temp = NULL;
   Node* curr = head;
   Node* prev = NULL; //prev starts at NULL because curr starts at head                                                                                                                                     
   while(curr)
   {
      if(curr->getStudent().getFirstName() != target) //target not found, moves to next Node                                                                                                                
      {
         prev = curr;
         curr = curr -> getNext();
      }
      else
      {
         if(prev == NULL) //Node to be deleted is the first one in the list                                                                                                                                 
         {
            head = curr -> getNext(); //head points to next Node                                                                                                                                            
         }
         else //Node is in middle of list or at the end                                                                                                                                                     
            prev -> setNext(curr -> getNext()); //                                                                                                                                                          
         curr -> deleteStudent(); //releases dynamically allocated memory of Student                                                                                                                        
         delete curr; //releases dynamically allocated memory of Node                                                                                                                                       
         curr = NULL;
         del = true; //Because a Node is deleted, function sends back TRUE                                                                                                                                  
      }
   }
   return del;
}
