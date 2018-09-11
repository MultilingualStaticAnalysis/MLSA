#include <stdio.h>  
#include "/usr/include/python2.7/Python.h"  

void makeDeposit(int amount, FILE* f) {
  char prog2[] = "Deposit.py";
  PyRun_SimpleFile(f, prog2);
  makeDeposit(900, f);
}

void checkBalance(int pin, FILE* f) {
  PyRun_SimpleFile(f, "Balance.py");
}

void transfer(FILE* f) {
  PyRun_SimpleFile(f, "Transfer.py");
}

void addNewAccount(char type, FILE* f) {
  char prog1[] = "addAccount.py";
  PyRun_SimpleFile(f, "Welcome.py");
  PyRun_SimpleFile(f, prog1);
}
  
int main()  
{ 
  FILE* f;
  
  f = fopen("Welcome.py", "r");
  Py_Initialize();
  PyRun_SimpleFile(f, "Welcome.py");
  makeDeposit(500, f);
  checkBalance(3827, f);
  transfer(f);
  addNewAccount('c', f);
  Py_Finalize();  
  return 0;  
} 
