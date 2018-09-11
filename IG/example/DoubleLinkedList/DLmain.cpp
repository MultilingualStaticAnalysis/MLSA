/*                                                                                                                                                                                                          
Anne Marie Bogar                                                                                                                                                                                            
November 29, 2014                                                                                                                                                                                           
Data Structures                                                                                                                                                                                             
Double Linked List Driver File                                                                                                                                                                              
A double linked list is created from the student information stored in an external file.                                                                                                                    
The user can add students to the list. If any students with the name Christine are added to the list, those students are deleted.                                                                           
Then a new list identical to the old list is created and sorted alphabetically by first name.                                                                                                               
A second list identical to the original list is created and sorted in descending alphabetical order.                                                                                                        
A third list is created with all the same students, but already sorted in alphabetical order.                                                                                                               
*/

#include "DoubleLinkedList.h"
#include <fstream>
void createStudent(string& f, string& l, char& m, int& ssn, int& a);
void setUp(DoubleLinkedList& list);
void finish(DoubleLinkedList& list);

int main()
{
   DoubleLinkedList list;
   Node* nPtr;
   string f, l;
   int n, ssn, a, count = -1;
   char ans = 'y', m;
   bool del;

   setUp(list); //updates list with info from the file                                                                                                                                                      
   cout << endl << "Do you want to add students to your list? y/n: ";
   cin >> ans;
   while(ans == 'y' || ans == 'Y')
   {
      createStudent(f, l, m, ssn, a);
      nPtr = new Node(f, l, m, ssn, a); //creates new Node (which nPtr points to) with the Student object just created                                                                                      
      list.append(nPtr); //appends the newly created Node to the list                                                                                                                                       
      cout << "\nAdd a new student to the list? y/n: ";
      cin >> ans;
   } //Nodes will be created until user does not enter y or Y                                                                                                                                               

   cout << "Student list (" << list.getNumNode() << " students):" << endl << endl;
   list.displayAscending(); //displays list from head to tail                                                                                                                                               
   cout << "\nStudent list displayed in descending order:" << endl << endl;
   list.displayDescending(); //displays list from tail to head                                                                                                                                              

   do
   {
      count++; //counts to see how many times deleteNode() was called                                                                                                                                       
      del = list.deleteNode("Christine"); //deletes all Nodes with the name Christine                                                                                                                       
   }while(del); //continue to delete Nodes until there are no more Christines in the list                                                                                                                   
   if(count > 0) //if any Nodes were deleted, the list will print again                                                                                                                                     
   {
      cout << "\nAfter Christine has been deleted from list:\n\n";
      list.displayAscending();
      cout << "\nlist is descending order without Christine:\n\n";
      list.displayDescending();
   }

   DoubleLinkedList L1(list); //creates a copy of the list                                                                                                                                                  
   DoubleLinkedList L2(list);
   L1.sort(); //sorts the list alphabetically                                                                                                                                                               
   cout << "\nList sorted in ascending order:\n\n";
   L1.displayAscending();
   L2.sort(false); //sorts the list descending alphabetically                                                                                                                                               
   cout <<"\nList sorted in descending order:\n\n";
   L2.displayAscending();


   DoubleLinkedList L3(list, true); //creates a copy of list, but sorted                                                                                                                                    
   cout << "\nSORTED list copied from original list ("  << L3.getNumNode() << " students):" << endl << endl;
   L3.displayAscending();
   cout << "\nSorted list displayed in descending order\n\n:";
   L3.displayDescending();

// finish(list); //save Students from L2 into the file                                                                                                                                                      

   return 0;
}

void createStudent(string& f, string& l, char& m, int& ssn, int& a)
//initializes all variables necessary to create a Student object                                                                                                                                            
//the variables are called by reference so that they can be used in the main function                                                                                                                       
{
   cout << endl <<"Enter first name: ";
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

void setUp(DoubleLinkedList& list) //updates the list with the existing Student information from the file StudentData.txt                                                                                   
{
   Student* sPtr;
   Student s;
   Node* nPtr;
   ifstream in_stream;
   string temp;

   in_stream.open("StudentData.txt"); // opens file StudentData.txt                                                                                                                                         
   if(in_stream.fail()) // If the file does not open, the program will exit                                                                                                                                 
   {
      cout << "Input file opening failed.\n";
      exit(1);
   }

   while(in_stream >> s) // reads in the values from the file to the end of the file                                                                                                                        
   {
      sPtr = new Student(s);
      nPtr = new Node(sPtr);
      list.append(nPtr);
   }
   in_stream.close(); // closes the file                                                                                                                                                                    
}

void finish(DoubleLinkedList& list) //saves the Student information in the list into the file StudentData.txt
{
   ofstream out_stream;

   out_stream.open("StudentData.txt"); // opens file StudentData.txt                                                                                                                                        
   if(out_stream.fail()) // If the file cannot open, the program ends                                                                                                                                       
   {
      cout << "Output file opening failed.\n";
      exit(1);
   }

   Node* curr = list.getHead();
   while(curr) //goes through all Nodes                                                                                                                                                                     
   {
      curr -> getStudent().print(out_stream); //prints Student information into the file                                                                                                                    
      curr = curr -> getNext(); //goes to the next Node in the list                                                                                                                                         
   }

   out_stream.close(); // closes the file                                                                                                                                                                   
}

