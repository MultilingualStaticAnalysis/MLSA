// Anne Marie Bogar                                                                                                                                                                                         
// November 20, 2013                                                                                                                                                                                        
// Lab 09                                                                                                                                                                                                   

#include <iostream>
#include <vector>
using namespace std;
void permutation(vector<int> v, vector<int>* pv, int n);
void fill(vector<int>* pv, int start, int end, vector<int> v, int num);
vector<int> perm(vector<int> v, int n);
void swap(vector<int>& v, int current, int other);
void display(vector<int>* pv);

int main()
{
   vector<int> list;
   //vector<vector<int> > perm_list;                                                                                                                                                                        
   int num;
   char choice = 'y';
   while(choice == 'y' || choice == 'Y')
   {
      cout << "Please enter an integer: ";
      cin >> num;
      list.push_back(num);
      cout << "Would you like to add another number? Enter Y or y to do so, and any other character to quit: ";
      cin >> choice;
   }
   int perm_num = 0;
   for(int k = 1; k < list.size(); k++)
      perm_num = perm_num*k;
   vector<int>* p = new vector<int>[perm_num];
   permutation(list, p, 0);
   display(p);
   delete [] p;
   return 0;
}

void permutation(vector<int> v, vector<int>* pv, int n)
{
   int perm_num = 1, p = 0;
   std::vector<int>::iterator it;
   for(int k = 1; k < v.size(); k++)
      perm_num = perm_num*k;
   int num = perm_num/v.size();

   if(n < num)
      permutation(v, pv, ++n);
   n--;

   vector<int> temp = v;
   temp.erase(temp.begin() + n);
   int m = n*num;
   int start = m-1, end = m+num-1;
   fill(pv, start, end, temp, num);

   for(int q = start; q <= end; q++)
   {
      it = pv[q].begin();
      pv[q].insert(it, 1, v[n]);
   }
}

void fill(vector<int>* pv, int start, int end, vector<int> v, int num)
{
   int p = 1;
   for(int k = start; k <= end; k++)
   {
      for(int j = 0; j < v.size(); j++)
         pv[k].push_back(v[j]);
   }

   for(int m = start+1; m <= end; m++)
   {
      pv[m] = perm(pv[m], p);
      p++;
   }
}

vector<int> perm(vector<int> v, int n)
{
   int q = 1;
   for(int k = 0; k < n; k++)
   {
      swap(v, 0, q);
      q++;
      if(q > v.size())
         q = 1;
   }
}

void swap(vector<int>& v, int current, int other)
{
   int temp = v[current];
   v[current] = v[other];
   v[other] = temp;
}

void display(vector<int>* pv)
{
   vector<int> temp;
   for(int k = 0; k < pv->size(); k++)
   {
      temp = pv[k];
      cout << "{ ";
      for(int j = 0; j < pv[k].size(); j++)
         cout << temp[j] << " ";
      cout << "}" << endl;
   }
}

