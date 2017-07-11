#include <iostream>
#include <python2.7/Python.h>
using namespace std;

int retrievePassWord(){
  return 1;
}

string retrieveUserName(){
  return "user name";
}

void verifyLoginInfo(int p, string u){
  FILE* f;
  Py_Initialize();
  PyRun_SimpleFile(f, "verifyAccount.py");
  Py_Finalize();
}

int main(){
  int password = retrievePassWord();
  string username = retrieveUserName();
  verifyLoginInfo(password, username);
  return 0;
}
