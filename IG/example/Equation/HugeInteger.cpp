//Anne Marie Bogar                                                                                                                                                                                          
//September 26, 2014                                                                                                                                                                                        
//Data Structures                                                                                                                                                                                           
//HugeInteger Source File                                                                                                                                                                                   

#include <iostream>
#include <string>
#include <vector>
#include "HugeInteger.h"
using namespace std;

HugeInteger::HugeInteger()//initializes default HugeInteger constructor to an array with all 0                                                                                                              
{
   for(int m=0; m<MAXDIGITS; m++)
      digits[m] = 0;
   sign = '+';
}

HugeInteger::HugeInteger(vector<char> vec)
{
   for(int m=0; m<MAXDIGITS; m++)
      digits[m] = 0;

   for(int k=0; k<vec.size(); k++)
      num.push_back(int(vec[k])-int('0'));

   for(int j=num.size()-1, m=0; j>=0; j--, m++)//number in array is backwards for easier calculation                                                                                                        
      digits[m] = num[j];
}

HugeInteger::HugeInteger(vector<int> vec)
{
   for(int m=0; m<MAXDIGITS; m++)
      digits[m] = 0;

   for(int k=0; k<vec.size(); k++)//vector resulting from +, *, or - is backwards                                                                                                                           
      digits[k] = vec[k];

   for(int j=vec.size()-1; j>=0; j--)
      num.push_back(vec[j]);
}

HugeInteger::HugeInteger(vector<int> vec, char s)
{
   sign = s;
   for(int m=0; m<MAXDIGITS; m++)
      digits[m] = 0;

   for(int k=0; k<vec.size(); k++)//vector resulting from +, *, or - is backwards                                                                                                                           
      digits[k] = vec[k];

   for(int j=vec.size()-1; j>=0; j--)
      num.push_back(vec[j]);
}


HugeInteger& HugeInteger::operator =(const HugeInteger& h2)//allows an existing HugeInteger to be assigned another existing HugeInteger                                                                     
{
   for(int k=0; k<MAXDIGITS; k++)
      digits[k] = 0;
   for(int k=0; k<MAXDIGITS; k++)
      digits[k] = h2.digits[k];
   num.erase(num.begin(), num.begin()+num.size());
   for(int k=0; k<h2.num.size(); k++)
      num.push_back(h2.num[k]);
   sign = h2.sign;

   return *this;
}

bool HugeInteger::isZero() const//checks to see if the value of a HugeInteger is 0                                                                                                                          
{
   return ((num.size() == 1) && (num[0] == 0));
}

bool HugeInteger::isBad() const //checks to see if the HugeInteger is bad (meaning it exceeded MAXDIGITS)                                                                                                   
{
   bool bad = false;
   if(num.size() == 2)
   {
      if(num[0] == 0 && num[1] == 0)
      {
         bad = true;
         cout << "Error! Number exceeds digit limit of HugeInteger" << endl << endl;
      }
   }
   return bad;
}

HugeInteger HugeInteger::returnBad() const //If an entered number or resultant number exceeds MAXDIGITS, a "bad" HugeInteger will be sent back                                                              
{
   vector<int> f;
   f.push_back(0);
   f.push_back(0); //a bad HugeInteger has a vector of 00                                                                                                                                                   
   HugeInteger fail(f);
   return fail;
}

bool HugeInteger::overflow(vector<int> v) const //checks if the vector size exceeds MAXDIGITS. Used before a HugeInteger is created                                                                         
{
   return (v.size() > MAXDIGITS);
}

bool HugeInteger::overflow(vector<char> v) const //same as above, but used in the overloaded >> operator                                                                                                    
{
   return ((v.size() > MAXDIGITS)||(v.size() == 0));
}

void HugeInteger::setUp(const HugeInteger& h, int a1[], int a2[], int& len1, int& len2, char& s) const //sets up the arrays and lengths for the multiplication and subtraction operations (in subtraction, \
the smaller HugeInteger is subtracted from the larger one, and in multilpication, the distinction is necessary to avoid excess zeros)                                                                       
{
   if(*this >= h)
   {
      len1 = num.size();
      len2 = h.num.size();
      for(int m=0; m<MAXDIGITS; m++)
      {
         a1[m] = digits[m]; //temporary arrays are given the same value as the digits array of the HugeIntegers so that they can be used interchangeably                                                    
         a2[m] = h.digits[m];
      }
   }
   else
   {
      len1 = h.num.size();
      len2 = num.size();
      for(int m=0; m<MAXDIGITS; m++)
      {
         a1[m] = h.digits[m];
         a2[m] = digits[m];
      }
      s = '-';
   }
}

HugeInteger HugeInteger::operator +(const HugeInteger& h2) const //two HugeIntegers are added together. The sum is sent back                                                                                
{
   HugeInteger ans;
   vector<int> sum;
   int length, number, carryOver = 0;
   if(*this >= h2)
      length = num.size();
   else
      length = h2.num.size();

   for(int k=0; k<length-1; k++)
   {
      number = carryOver + digits[k] + h2.digits[k];
      sum.push_back(number%10); //the number on the ones place goes into sum                                                                                                                                
      carryOver = number/10; //the number in the tens place goes into carryOver
   }

   number = carryOver + digits[length-1] + h2.digits[length-1];
   sum.push_back(number%10); //because the number is calculated backwards, the number in the ones place is added in first                                                                                   
   if(number/10 != 0)
      sum.push_back(number/10);

   if(overflow(sum)) //if sum exceeds the limit size (MAXDIGITS), then a bad HugeInteger will be returned                                                                                                   
      ans = returnBad();
   else
   {
      HugeInteger hi(sum);
      ans = hi;
   }

   return ans;
}

HugeInteger HugeInteger::operator -(const HugeInteger& h2) const
{
   vector<int> difference;
   int a1[MAXDIGITS] = {0}, a2[MAXDIGITS] = {0};
   int length, number, temp;
   char s = '+';
   setUp(h2, a1, a2, length, temp, s); //a1 and a2 are initialized depending on which HugeInteger is bigger                                                                                                 

   for(int k=0; k<length; k++)
   {
      if(a1[k] < a2[k])
      {
         a1[k] += 10;
         a1[k+1]--;
      }
      difference.push_back(a1[k] - a2[k]);
   }
   if(difference.size() != 1)
   {
      number = difference[difference.size()-1];
      while(number == 0 && difference.size() != 1) //gets rid of excess zeros at the beginning of the vector (ex: 77 - 76 = 01)                                                                             
      {
         difference.pop_back();
         number = difference[difference.size()-1];
      }
   }

   HugeInteger hi(difference, s);
   return hi;
}

HugeInteger HugeInteger::operator *(const HugeInteger& h2) const
{
   vector<int> sum;
   vector<int> v;
   v.push_back(0);
   HugeInteger product(v);
   if(isZero() || h2.isZero())//multiplying a number by 0 will always be 0                                                                                                                                  
      return product;
   int a1[MAXDIGITS] = {0}, a2[MAXDIGITS] = {0};
   int len1, len2, number, carryOver;
   char temp;
   setUp(h2, a1, a2, len1, len2, temp); ////a1, a2, and their corresponding lengths are initialized depending on which HugeInteger is bigger                                                                
   for(int k=0; k<len2; k++)
   {
      carryOver = 0;
      for(int m=0; m<k; m++) //adds zeros to the end of the number (like how 23*48 is really 23*8 + 23*40)                                                                                                  
         sum.push_back(0);

      for(int j=0; j<len1-1; j++)
      {
            number = a2[k]*a1[j];
            number += carryOver;
            sum.push_back(number%10);
            carryOver = number/10;
      }
      number = a2[k]*a1[len1-1];
      number += carryOver;
      sum.push_back(number%10); //because the sum is calculated backwards, the number in the ones place is added in first                                                                                   
      if(number/10 != 0)
         sum.push_back(number/10);

      if(overflow(sum))//if at least one sum exceeds MAXDIGITS, then the product will exceed, so a bad HugeInteger is returned                                                                              
      {
         product = returnBad();
         break;
      }
      else
      {
         HugeInteger hi(sum);
         product = product + hi;//the calculation is broken up (23*48 -> 23*8 + 23*40), so each part is added back up in product                                                                            
         sum.erase(sum.begin(), sum.begin()+sum.size());//sum must be erased so that it can start fresh when the for-loop goes again
      }
   }
   return product;
}

bool HugeInteger::operator ==(const HugeInteger& h2) const //determines if the value of two HugeIntegers are equal                                                                                          
{
   return (!(*this > h2) && !(h2 > *this));
}

bool HugeInteger::operator !=(const HugeInteger& h2) const //determines if the value of two HugeIntegers are not equal                                                                                      
{
   return !(*this == h2);
}

bool HugeInteger::operator >(const HugeInteger& h2) const//decides if one HugeInteger's value is greater than another's                                                                                     
{
   int count = 0;
   bool greaterThan = true;
   if(num.size() < h2.num.size())
      greaterThan = false;
   else if(num.size() == h2.num.size())
   {
      for(int k=0; k<num.size(); k++)
      {
         if(num[k] < h2.num[k])
         {
            greaterThan = false;
            break;
         }
         else if(num[k] > h2.num[k])
         {
            greaterThan = true;
            break;
         }
         else
            count++;
      }
      if(count == num.size())
         greaterThan = false;
   }
   return greaterThan;
}

bool HugeInteger::operator >=(const HugeInteger& h2) const //decides if one HugeInteger's value is greater than or equal to another's                                                                       
{
   return((*this > h2)||(*this == h2));
}

bool HugeInteger::operator <=(const HugeInteger& h2) const //decides if one HugeInteger's value is less than or equal to another's                                                                          
{
   return(!(*this > h2)||(*this == h2));
}

ostream& operator <<(ostream& outs, const HugeInteger& hi) //displays the HugeInteger's value                                                                                                               
{
   if(hi.sign == '-')
      cout << hi.sign;
   for(int k=0; k<hi.num.size(); k++)
      outs << hi.num[k];
   return outs;
}

istream& operator >>(istream& ins, HugeInteger& hi) //takes in the input as characters and creates a HugeInteger                                                                                            
{
   char c, d;
   int i;
   vector<char> v;

   do //weeds through input until a number or comma is found                                                                                                                                                
   {
      ins >> c;
      i = c;// converts c into an integer using the ASCII value chart                                                                                                                                       
   }while(!((i >= 48 && i <= 57)||(i == 44)));

   ins.putback(c); //puts retrieved input value back so that another variable can retrieve it                                                                                                               

   while((i >= 48 && i <= 57)||(i == 44)) //48 - 57 corresponds to characters 0-9 and 44 corresponds to the comma character                                                                                 
   {
      ins >> d;
      if(i >= 48 && i <=57) //excludes commas from the vector                                                                                                                                               
         v.push_back(d);
      c = ins.peek(); //sees the first input value, but does not retrieve it                                                                                                                                
      i = c;
   }

   if(hi.overflow(v)) //if the input vector's size exceeds MAXDIGITS, a bad HugeInteger will be returned                                                                                                    
      hi = hi.returnBad();
   else
   {
      HugeInteger h(v);
      hi = h;
   }

   return ins;
}
