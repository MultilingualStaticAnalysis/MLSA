/*                                                                                                                                                                                                          
Anne Marie Bogar                                                                                                                                                                                            
November 12, 2014                                                                                                                                                                                           
Data Structures                                                                                                                                                                                             
Linked List Driver File                                                                                                                                                                                     
The program lets the user create a list of Student objects (with first name, last name, middle initial, social security number, and age).                                                                   
Then the program deletes any Student with the first name Chrsitine.                                                                                                                                         
The list is copied and then that copied list is sorted using the bubbleSort() method.                                                                                                                       
The list is copied again and then sorted using the selectionSort() method.                                                                                                                                  
Finally, the program creates a new list that is identical to the user's list, but all the Students are sorted by age.                                                                                       
The Student information is then stored in a file and retrieved at the beginning of the program                                                                                                              
*/

#include "Student.h"
#include "Node.h"
#include "LinkedList.h"
#include <fstream>
using namespace std;
void createStudent(string& f, string& l, char& m, int& ssn, int& a);
void setUp(LinkedList<Student>& list);
void finish(LinkedList<Student>& list);

int main()
{
   LinkedList<Student> list;
   Node<Student>* nPtr;
   string f, l;
   int n, ssn, a, count = -1;
   char ans = 'y', m;
   bool del;

   //setUp(list); //updates list with info from the file                                                                                                                                                    
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
   list.display(); //displays list                                                                                                                                                                          

   do
   {
      count++; //counts to see how many times deleteNode() was called                                                                                                                                       
      del = list.deleteNode("Christine"); //deletes all Nodes with the name Christine                                                                                                                       
   }while(del); //continue to delete Nodes until there are no more Christines in the list                                                                                                                   
   if(count > 0) //if any Nodes were deleted, the list will print again                                                                                                                                     
   {
      cout << "\nAfter Christine has been deleted from list:" << endl << endl;
      list.display();
   }
/*                                                                                                                                                                                                          
   LinkedList bubble(list); //create copy of list                                                                                                                                                           
   cout << "\ndisplaying copied list:\n\n";
   bubble.display();                                                                                                                                                                                        
   bubble.bubbleSort(); //sorts the new list by bubble sort                                                                                                                                                 
   cout << "\ndisplaying bubble sorted list:\n\n";                                                                                                                                                          
   bubble.display();                                                                                                                                                                                        
                                                                                                                                                                                                            
   LinkedList selection(list); //create copy of list                                                                                                                                                        
   cout << "\ndisplaying copied list:\n\n";                                                                                                                                                                 
   selection.display();                                                                                                                                                                                     
   selection.selectionSort(); //sorts new list by selection sort                                                                                                                                            
   cout << "\ndisplaying selection sorted list:\n\n";                                                                                                                                                       
   selection.display();                                                                                                                                                                                     
*/
   LinkedList L2(list, true); //creates a copy of list, but sorted                                                                                                                                          
   cout << "\nSORTED list copied from original list ("  << L2.getNumNode() << " students):" << endl << endl;
   L2.display();

   //finish(list); //save Students from L2 into the file                                                                                                                                                    
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

void setUp(LinkedList<Student>& list) //updates the list with the existing Student information from the file StudentData.txt                                                                                
{
   Student* sPtr;
   Student s;
   Node<Student>* nPtr;
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

void finish(LinkedList<Student>& list) //saves the Student information in the list into the file StudentData.txt                                                                                            
{
   ofstream out_stream;

   out_stream.open("StudentData.txt"); // opens file StudentData.txt                                                                                                                                        
   if(out_stream.fail()) // If the file cannot open, the program ends                                                                                                                                       
   {
      cout << "Output file opening failed.\n";
      exit(1);
   }

   Node<Student>* curr = list.getHead();
   while(curr) //goes through all Nodes                                                                                                                                                                     
   {
      curr -> getStudent().print(out_stream); //prints Student information into the file                                                                                                                    
      curr = curr -> getNext(); //goes to the next Node in the list                                                                                                                                         
   }

   out_stream.close(); // closes the file                                                                                                                                                                   
}
