#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct price {
  int dollar;
  int cent;
};

struct product {
  price p;
  string substance;
};

int main()
{
  vector<string> array[10];
  array[1].push_back("Hello");
  array[1].back().size();
  price pr;
  pr.dollar = 3;
  product floss;
  floss.p = pr;
  vector<int> yo[10];
  yo[2].push_back(floss.p.dollar);
  yo[3].push_back(array[1].back().size());
  yo[4].push_back(array[1].back().size()+1);
  return 0;
}