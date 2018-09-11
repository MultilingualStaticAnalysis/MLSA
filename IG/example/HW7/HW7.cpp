// Anne Marie Bogar                                                                                                                                                                                         
// October 9, 2013                                                                                                                                                                                          
// Homework 7 problem #2                                                                                                                                                                                    
// Modify the attached definition of class Money so that all the following are added:                                                                                                                       
// (1) The operator <, <=, >, >= have each been overloaded to apply to the type Money                                                                                                                       
// (2) The following member function Money percent(int percent_figure) const; has been added to the class definition.                                                                                       

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cctype>
using namespace std;
class Money
{
   public:
      friend Money operator +(const Money& amount1, const Money& amount2);
      friend Money operator -(const Money& amount1, const Money& amount2);
      friend Money operator -(const Money& amount);
      friend bool operator ==(const Money& amount1, const Money& amount2);
      friend bool operator <(const Money& amount1, const Money& amount2);
      friend bool operator <=(const Money& amount1, const Money& amount2);
      friend bool operator >(const Money& amount1, const Money& amount2);
      friend bool operator >=(const Money& amount1, const Money& amount2);
      Money(long dallars, int cents);
      Money(long dollars);
      Money();
      double get_value() const;
      // Returns the value of the Money variable as a double (0.00 form)                                                                                                                                    
      Money percent(int percent_figure) const;
      // Return a percentage of the money amount in the calling object                                                                                                                                      
      friend istream& operator >>(istream& ins, Money& amount);
      //Overloads the >> operator so it can be used to input values of type Money.                                                                                                                          
      //Notation for inputting negative amounts is as in -$100.00.                                                                                                                                          
      //Precondition: If ins is a file input stream, then ins has already been                                                                                                                              
      //connected to a file.                                                                                                                                                                                
      friend ostream& operator <<(ostream& outs, const Money& amount);
      //Overloads the << operator so it can be used to output values of type Money.                                                                                                                         
      //Precedes each output value of type Money with a dollar sign.                                                                                                                                        
      //Precondition: If outs is a file output stream,                                                                                                                                                      
      //then outs has already been connected to a file.                                                                                                                                                     
   private:
      long all_cents;
};
int digit_to_int(char c);
//Used in the definition of the overloaded input operator >>.                                                                                                                                               
//Precondition: c is one of the digits '0' through '9'.                                                                                                                                                     
//Returns the integer for the digit; for example, digit_to_int('3') returns 3.                                                                                                                              

int main( )
{
/* Money amount;                                                                                                                                                                                            
   ifstream in_stream;                                                                                                                                                                                      
   ofstream out_stream;                                                                                                                                                                                     
                                                                                                                                                                                                            
   in_stream.open("infile.dat");                                                                                                                                                                            
   if (in_stream.fail( ))                                                                                                                                                                                   
   {                                                                                                                                                                                                        
      cout << "Input file opening failed.\n";                                                                                                                                                               
      exit(1);
   }                                                                                                                                                                                                        
                                                                                                                                                                                                            
   out_stream.open("outfile.dat");                                                                                                                                                                          
   if (out_stream.fail( ))                                                                                                                                                                                  
   {                                                                                                                                                                                                        
      cout << "Output file opening failed.\n";                                                                                                                                                              
      exit(1);                                                                                                                                                                                              
   }                                                                                                                                                                                                        
                                                                                                                                                                                                            
   in_stream >> amount;                                                                                                                                                                                     
   out_stream << amount                                                                                                                                                                                     
              << " copied from the file infile.dat.\n";                                                                                                                                                     
   cout << amount                                                                                                                                                                                           
        << " copied from the file infile.dat.\n";                                                                                                                                                           
                                                                                                                                                                                                            
   in_stream.close( );                                                                                                                                                                                      
   out_stream.close( );                                                                                                                                                                                     
*/
   Money m1(987, 45), m2(12);
   cout << "m1 = $" << m1.get_value() << endl;
   cout << "m2 = $" << m2.get_value() << endl;
   Money m3(m1.percent(5));
   Money m4(m2.percent(35));
   cout << "5% of m1 = $" << m3.get_value() << endl;
   cout << "35% of m2 = $" << m4.get_value() << endl;
   if (m3 == m4)
      cout << "They are equal!\n";
   else
      cout << "They are NOT equal.\n";
   if (m3 < m4)
     cout << "m3 is less than m4.\n";
   else
      cout << "m4 is less than m3.\n";
   if (m3 > m4)
      cout << "m3 is greater than m4.\n";
   else
      cout << "m4 is greater than m3.\n";
   if (m3 <= m4)
      cout << "m3 is less than or equal to m4.\n";
   else
      cout << "m4 is less than or equal to m3.\n";
   if (m3 >= m4)
      cout << "m3 is greater than or equal to m4.\n";
   else
      cout << "m4 is greater than or equal to m3.\n";
   Money m5(m1 - m2);
   cout << "m1 - m2 = $" << m5.get_value() << endl;
   Money m6(m1 + m2);
   cout << "m1 + m2 = $" << m6.get_value() << endl;
   Money m7(-m1);
   cout << "negative m1 = $" << m7.get_value() << endl;
   return 0;
}
//Uses iostream, cctype, cstdlib:                                                                                                                                                                           
istream& operator >>(istream& ins, Money& amount)
{
   char one_char, decimal_point,
      digit1, digit2; //digits for the amount of cents                                                                                                                                                      
   long dollars;
   int cents;
   bool negative;//set to true if input is negative.                                                                                                                                                        

   ins >> one_char;
   if (one_char == '-')
   {
      negative = true;
      ins >> one_char; //read '$'                                                                                                                                                                           
   }
   else
      negative = false;
   //if input is legal, then one_char == '$'                                                                                                                                                                

   ins >> dollars >> decimal_point >> digit1 >> digit2;

   if ( one_char != '$' || decimal_point != '.'
        || !isdigit(digit1) || !isdigit(digit2) )
   {
      cout << "Error illegal form for money input\n";
      exit(1);
   }

   cents = digit_to_int(digit1)*10 + digit_to_int(digit2);

   amount.all_cents = dollars*100 + cents;
   if (negative)
      amount.all_cents = -amount.all_cents;


   return ins;
}

int digit_to_int(char c)
{
   return ( static_cast<int>(c) - static_cast<int>('0') );
}

//Uses cstdlib and iostream:                                                                                                                                                                                
ostream& operator <<(ostream& outs, const Money& amount)
{
   long positive_cents, dollars, cents;
   positive_cents = labs(amount.all_cents);
   dollars = positive_cents/100;
   cents = positive_cents%100;

   if (amount.all_cents < 0)
      outs << "-$" << dollars << '.';
   else
      outs << "$" << dollars << '.';

   if (cents < 10)
      outs << '0';
   outs << cents;

   return outs;
}

Money::Money(long dollars, int cents)
{
   if (dollars*cents < 0)
   {
      cout << "Illegal values for dollars and cents.\n";
      exit(1);
   }
   all_cents = dollars *100 + cents;
}

Money::Money(long dollars) : all_cents(dollars * 100)
{
}

Money::Money() : all_cents(0)
{
}

double Money::get_value() const
{
   return(all_cents * 0.01);
}

Money Money::percent(int percent_figure) const
{
   double percent = percent_figure * 0.01;
   return Money (0.0, all_cents * percent);
}

Money operator +(const Money& amount1, const Money& amount2)
{
   Money temp;
   temp.all_cents = amount1.all_cents + amount2.all_cents;
   return temp;
}

Money operator -(const Money& amount1, const Money& amount2)
{
   Money temp;
   temp.all_cents = amount1.all_cents - amount2.all_cents;
   return temp;
}

Money operator -(const Money& amount)
{
   Money temp;
   temp.all_cents = -amount.all_cents;
   return temp;
}

bool operator ==(const Money& amount1, const Money& amount2)
{
   return (amount1.all_cents == amount2.all_cents);
}

bool operator <(const Money& amount1, const Money& amount2)
{
   return (amount1.all_cents < amount2.all_cents);
}

bool operator <=(const Money& amount1, const Money& amount2)
{
   return (amount1.all_cents <= amount2.all_cents);
}

bool operator >(const Money& amount1, const Money& amount2)
{
   return (amount1.all_cents > amount2.all_cents);
}

bool operator >=(const Money& amount1, const Money& amount2)
{
   return (amount1.all_cents >= amount2.all_cents);
}

