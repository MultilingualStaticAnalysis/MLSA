#include <iostream>
using namespace std;

void reverse(const char a[], int num_used);
int compute_average(const int a[], int num_used);
void fill_array(char a[], int size, int& num_used);
void fill_array(int a[], int size);
int find_max(int a[], int num_used, int& max_index);
void find_max_min(int a[], int num_used, int& max_index, int& min_index);

int main()
{
   char a[10];
   int b[10] = {0};
   int num_used, max_index, min_index;

   fill_array(a, 10, num_used);
   reverse(a, num_used);
   cout << endl;

   fill_array(b, 10);
   cout << "The average is " << compute_average(b, 10) << endl;
   cout << "The maximum value is " << find_max(b, 10, max_index);
   cout << ", which is found at index " << max_index << endl;
   find_max_min(b, 10, max_index, min_index);
   cout << "The maximum value is found at index " << max_index;
   cout << " and the minimum value is found at index " << min_index << endl;
   return 0;
}

void fill_array(char a[], int size, int& num_used)
{
   char c;
   num_used = 0;
   cout << "Enter up to 10 characters. Enter ';' to stop: ";
   for (int k = 0; k < size; k++)
   {
      cin >> c;
      if (c == ';')
         break;
      a[k] = c;
        num_used++;
   }
}

void fill_array(int a[], int size)
{
   cout << "Enter 10 letters. Separate each with a space: ";
   for (int k = 0; k < size; k++)
   {
      cin >> a[k];
   }
}

void reverse(const char a[], int num_used)
{
   for (int k = num_used - 1; k >= 0; k--)
   {
      cout << a[k] << ", ";
   }
   cout << endl;
}

int compute_average(const int a[], int num_used)
{
   int sum = 0;
   for (int k = 0; k < num_used; k++)
   {
      sum += a[k];
   }
   return sum/num_used;
}

int find_max(int a[], int num_used, int& max_index)
{
   int max = a[0];
   max_index = 0;
   for (int k = 1; k < num_used; k++)
   {
      if(a[k] > max)
      {
         max = a[k];
         max_index = k;
      }
   }
   return max;
}

void find_max_min(int a[], int num_used, int& max_index, int& min_index)
{
   int max = a[0], min = a[0];
   max_index = 0;
   min_index = 0;
   for (int k = 1; k < num_used; k++)
   {
      if (a[k] > max)
      {
         max = a[k];
         max_index = k;
      }
      if (a[k] < min)
      {
         min = a[k];
         min_index = k;
      }
   }
}
