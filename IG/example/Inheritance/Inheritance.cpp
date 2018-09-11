#include <iostream>
using namespace std;

class base1 {
protected:
  int i;
public:
  base1(int x) { i = x; cout << "Constructing base1\n"; }
  ~base1() { cout << "Destructing base2\n"; }
};

class base2 {
protected:
  int k;
public:
  base2(int x) { k = x; cout << "Constructing base2\n"; }
  ~base2() { cout << "Destructing base2\n"; }
};

class derived: public base1, public base2 {
  int j;
public:
  derived(int x, int y, int z): base1(y), base2(z)
    { j = x; cout << "Constructing derived\n"; }

  ~derived() { cout << "Destructing derived\n"; }
  void show() { cout << i << " " << j << " " << k << "\n"; }
};

int main()
{
  derived ob(3, 4, 5);

  ob.show();  // displays 4 3 5

  return 0;
}
