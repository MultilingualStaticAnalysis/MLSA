// Anne Marie Bogar                                                                                                                                                                                         
// September 15, 2014                                                                                                                                                                                       
// HugeInteger Tester                                                                                                                                                                                       

#include <iostream>
#include <vector>
#include <string>
using namespace std;
vector<int> add(int[], int[], int len1, int len2);
bool check(vector<int> v);
bool equalTo(vector<int> v1, vector<int> v2);
bool notEqual(vector<int> v1, vector<int> v2);
bool greaterThanOrEqual(vector<int> v1, vector<int> v2);
bool lessThanOrEqual(vector<int> v1, vector<int> v2);

int main()
{
   int a, b;
   char c;
   cout << "enter equation: ";
   cin >> a >> c >> b;
   cout << a << " " << c << " " << b << endl;

   vector<int> v;                                                                                                                                                                                           
   int array1[7] = {1, 9, 5, 3, 6, 0, 0};                                                                                                                                                                   
   int len1 = 5;                                                                                                                                                                                            
   int array2[7] = {4, 8, 2, 2, 0, 1, 3};                                                                                                                                                                   
   int len2 = 7;                                                                                                                                                                                            
   v = add(array1, array2, len1, len2);                                                                                                                                                                     
   for(int k=0; k<v.size(); k++)                                                                                                                                                                            
      cout << v[k] << " ";                                                                                                                                                                                  
   cout << endl;                                                                                                                                                                                            
                                                                                                                                                                                                            
   int a1[8] = {1, 3, 7, 2, 0, 7, 7, 8};                                                                                                                                                                    
   int a2[8] = {7, 3, 4, 0, 0, 0, 0, 0};                                                                                                                                                                    
   len1 = 8;                                                                                                                                                                                                
   len2 = 3;                                                                                                                                                                                                
   v = add(a1, a2, len1, len2);                                                                                                                                                                             
   for(int k=0; k<v.size(); k++)                                                                                                                                                                            
      cout << v[k] << " ";                                                                                                                                                                                  
   cout << endl << endl;                                                                                                                                                                                    
                                                                                                                                                                                                            
   //add(array1, array2);                                                                                                                                                                                     
   cout << endl;                                                                                                                                                                                            
   //add(a1, a2);                                                                                                                                                                                             
   cout << endl;                                                                                                                                                                                            
                                                                                                                                                                                                            
   vector<int> num1, num2;                                                                                                                                                                                  
   for(int k=0; k<7; k++)                                                                                                                                                                                   
      num1.push_back(k);                                                                                                                                                                                    
   for(int j=3; j>=0; j--)                                                                                                                                                                                  
      num2.push_back(j);                                                                                                                                                                                    
                                                                                                                                                                                                            
   if(equalTo(num1, num2))                                                                                                                                                                                  
      cout << "EQUAL!!" << endl;                                                                                                                                                                            
   else                                                                                                                                                                                                     
      cout << "NOT EQUAL!!!" << endl;                                                                                                                                                                       
                                                                                                                                                                                                            
   if(equalTo(num1, num1))
      cout << "EQUAL!!!" << endl;                                                                                                                                                                           
   else                                                                                                                                                                                                     
      cout << "NOT EQUAL!!" << endl;                                                                                                                                                                        
                                                                                                                                                                                                            
   if(notEqual(num1, num2))                                                                                                                                                                                 
      cout << "NOT EQUAL!!" << endl;                                                                                                                                                                        
   else                                                                                                                                                                                                     
      cout << "EQUAL!!!" << endl;                                                                                                                                                                           
                                                                                                                                                                                                            
   if(notEqual(num1, num1))                                                                                                                                                                                 
      cout << "NOT EQUAL!!!" << endl;                                                                                                                                                                       
   else                                                                                                                                                                                                     
      cout << "EQUAL!!" << endl;                                                                                                                                                                            
                                                                                                                                                                                                            
   if(greaterThanOrEqual(num1, num2))                                                                                                                                                                       
      cout << "Greater Than Or Equal To!!" << endl;                                                                                                                                                         
   else                                                                                                                                                                                                     
      cout << "Less Than!!!" << endl;                                                                                                                                                                       
                                                                                                                                                                                                            
   if(greaterThanOrEqual(num1, num1))                                                                                                                                                                       
      cout << "Greater than or Equal to!!!" << endl;                                                                                                                                                        
   else                                                                                                                                                                                                     
      cout << "Less Than!!" << endl;                                                                                                                                                                        
                                                                                                                                                                                                            
   if(greaterThanOrEqual(num2, num1))                                                                                                                                                                       
      cout << "Greater than or Equal to!!!" << endl;                                                                                                                                                        
   else                                                                                                                                                                                                     
      cout << "Less Than!!" << endl;                                                                                                                                                                        
                                                                                                                                                                                                            
   if(lessThanOrEqual(num1, num2))
      cout << "Less Than Or Equal To!!" << endl;                                                                                                                                                            
   else                                                                                                                                                                                                     
      cout << "Greater Than!!!" << endl;                                                                                                                                                                    
                                                                                                                                                                                                            
   if(lessThanOrEqual(num1, num1))                                                                                                                                                                          
      cout << "Less than or Equal to!!!" << endl;                                                                                                                                                           
   else                                                                                                                                                                                                     
      cout << "Greater Than!!" << endl;                                                                                                                                                                     
                                                                                                                                                                                                            
   if(lessThanOrEqual(num2, num1))                                                                                                                                                                          
      cout << "Less than or Equal to!!!" << endl;                                                                                                                                                           
   else                                                                                                                                                                                                     
      cout << "Greater Than!!" << endl;                                                                                                                                                                     

   return 0;
}

vector<int> add(int arr1[], int arr2[], int len1, int len2)
{
   vector<int> sum;
   int length, number, carryOver = 0;
   if(len1 > len2)
      length = len1;
   else
      length = len2;

   cout << length << endl;

   for(int k=0; k<length-1; k++)
   {
      number = carryOver + arr1[k] + arr2[k];
      sum.push_back(number%10);
      carryOver = number/10;
   }

   number = carryOver + arr1[length-1] + arr2[length-1];
   sum.push_back(number%10);
   if(number/10 != 0)
      sum.push_back(number/10);

   if(check(sum))
   {
      return sum;
   }
   else
   {
      return sum;
   }
}

bool check(vector<int> v)
{
   if(v.size() < 40)
      return true;
   else
      return false;
}

bool equalTo(vector<int> v1, vector<int> v2)
{
   if(v1.size() != v2.size())
      return false;
   else
   {
      int count = 0;
      for(int k=0; k<v1.size(); k++)
      {
         if(v1[k] == v2[k])
            count++;
      }
      if(count == v1.size())
         return true;
      else
         return false;
   }
}

bool notEqual(vector<int> v1, vector<int> v2)
{
   if(v1.size() != v2.size())
      return true;
   else
   {
      for(int k=0; k<v1.size(); k++)
      {
         if(v1[k] != v2[k])
            return true;
      }
      return false;
   }
}

bool greaterThanOrEqual(vector<int> v1, vector<int> v2)
{
   if(v1.size() > v2.size())
      return true;
   else if(v1.size() < v2.size())
      return false;
   else
   {
      for(int k=0; k<v1.size(); k++)
      {
         if(v1[k] > v2[k])
            return true;
         if(v1[k] < v2[k])
            return false;
      }
      return true;
   }
}

bool lessThanOrEqual(vector<int> v1, vector<int> v2)
{
   if(v1.size() < v2.size())
      return true;
   else if(v1.size() > v2.size())
      return false;
   else
   {
      for(int k=0; k<v1.size(); k++)
      {
         if(v1[k] < v2[k])
            return true;
         if(v1[k] > v2[k])
            return false;
      }
      return true;
   }

}
