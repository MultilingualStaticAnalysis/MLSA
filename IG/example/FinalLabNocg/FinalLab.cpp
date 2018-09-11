/*                                                                                                                                                                                                          
 Anne Marie Bogar                                                                                                                                                                                           
 May 10, 2016                                                                                                                                                                                               
 Final Lab                                                                                                                                                                                                  
 Measures the size of disk files under a given directory tree                                                                                                                                               
 (e.g., your home directory, or all students home directories),                                                                                                                                             
 and in the end, output results that can be used by Excel                                                                                                                                                   
 or other graphing tools to draw histogram of disk file size distribution                                                                                                                                   
                                                                                                                                                                                                            
 ****include the flag -std=c++0x when compiling                                                                                                                                                             
*/

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <cmath>
#include <sstream>
using namespace std;

int MAX_SIZE = 32;

int main(int argc, char *argv[])
{
   // must have exactly 2 arguments (a.out and the path to the directory)                                                                                                                                   
   if(argc =! 2)
   {
      cerr << "Error! Incorect number of arguments\n";
      return -1;
   }

   // system call to get all files in argv[1] directory                                                                                                                                                     
   string s = argv[1];
   system(("ls -Rl " + s + " | grep ^- > output.txt").c_str());

   //just get the file size and put it in a vector                                                                                                                                                          
   string line = "";
   int i = 1, k = 0;
   vector<int> v;
   ifstream in("output.txt");
   while(in >> line)
   {
      if(i==5)
      {
         k = atoi(line.c_str());
         v.push_back(k);
      }
      i++;
      if(i>9)
         i=1;
   }

   //count the number of files of a certain size and document in an array                                                                                                                                   
   //ex: if the size is 50, place in the 7th spot in array (32-64)                                                                                                                                          
   int num[MAX_SIZE] = {0};
   int result;
   for(int j = 0; j < v.size(); j++)
   {
      double temp = v[j];
      if(v[j] == 0)
      {
         result = 0;
         num[result] = num[result] + 1;
      } else {
         result = ilogb(temp); // finds closest 2^power                                                                                                                                                     
         num[result+1] = num[result+1] + 1;
      }
   }

   //writes the range, nuber of files, and percentage to a file                                                                                                                                             
   ofstream out;
   string str = "";
   out.open("excel.txt");
   if(out.is_open())
   {
      out << "range(KB):num_of_files:percentage(%)\n";
      for(int j=0; j<MAX_SIZE; j++)
      {
         string n="", p="", c="", f="";
         if(j==0) //if the file size is 0                                                                                                                                                                   
         {
            n = to_string(num[j]);
            p = to_string((double)num[j]/v.size()*100);
            str = "0-1:" + n + ":" + p + "\n";
         } else { //if file size is greater than 0                                                                                                                                                          
            n = to_string(num[j]); //number of files of certain size                                                                                                                                        
            p = to_string((double)num[j]/v.size()*100); // percentage
            //this is for the range                                                                                                                                                                         
            f = to_string(((int)pow(2.0, j)));
            c = to_string(((int)pow(2.0, (j-1))));
            if(j == 31)
               str = str + c + "" + f + ":" + n + ":" + p + "\n";
            else
               str = str + c + "-" + f + ":" + n + ":" + p + "\n";
         }
      }
      out << str; //writes string str to file                                                                                                                                                               
      out.close();
   }
   else
   {
      cerr << "Could not open file\n";
      return -1;
   }

   // display the file on the terminal                                                                                                                                                                      
   system("awk -F\":\" '{printf \"%-25s %-20s %-20s\\n\", $1,$2,$3}' excel.txt");

   return 0;
}
