#include <iostream>
#include <Python/Python.h>
using namespace std;
void A();
int main(){
  int x, y;
  x = 1;
  A();
  y = 2;
  return 0;
}
void A(){
  FILE *f = nullptr;
  string s = "test.py";
  Py_Initialize();
  PyRun_SimpleFile(f, s);
  Py_Finalize();
}
