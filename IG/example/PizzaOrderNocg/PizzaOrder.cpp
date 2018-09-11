#include <iostream>
#include <string>
using namespace std;

int main ()
{
   cout.setf(ios::fixed); // These three sets of lines tell the computer to                                                                                                                                 
   cout.setf(ios::showpoint); // output all double numbers so that they                                                                                                                                     
   cout.precision(2); // always have 2 decimal points, no more or less                                                                                                                                      
   string name;
   int twelve_inch, fourteen_inch;
   double total_amount, amount_recieved, change;

   cout << "Welcome to Little Italy Pizza\n";
   cout << "Please enter the customer's FIRST name: ";
   cin >> name;
   cout << "How many 12 inch pizzas are ordered? ";
   cin >> twelve_inch;
   cout << "How many 14 inch pizzas are ordered? ";
   cin >> fourteen_inch;

   total_amount = (twelve_inch * 12.39) + (fourteen_inch * 15.98);
   /* To find the total amount, multiply the amount of 12 inch pizzas and the        amount of 14 inch pizzas by how much they cost, and then add the two                                                   
      numbers together */
   cout << "Total amount due is: $" << total_amount << endl;
   cout << "The amount recieved from the customer: $";
   cin >> amount_recieved;
   change = amount_recieved - total_amount;

   cout << endl;
   cout << "------------------------------\n";
   cout << "Receipt by Little Italy Pizza\n";
   cout << "------------------------------\n";
   cout << "Customer's First Name: " << name << endl;
   cout << "------------------------------\n";
   cout << "Pizza    Num    Price\n";
   cout << "12-in    " << twelve_inch << "      $" << twelve_inch*12.39;
   // The number of 12 inch pizzas multiplied by the amount one pizza costs                                                                                                                                 
   // displays the total cost of 12 inch pizzas ordered                                                                                                                                                     
   cout << endl;
   cout << "14-in    " << fourteen_inch << "      $" << fourteen_inch*15.98;
   // Finding the total cost of 14 inch pizzas is similar to finding the total                                                                                                                              
   // cost for 12 inch pizzas                                                                                                                                                                               
   cout << endl;
   cout << "------------------------------\n";
   cout << "Total:          $" << total_amount << endl;
   cout << "Recieved:       $" << amount_recieved << endl;
   cout << "Change:         $" << change << endl;
   cout << "------------------------------\n";

   return 0;
}
