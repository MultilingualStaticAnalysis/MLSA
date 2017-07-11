#include <iostream>
#include <Python.h>
using namespace std;

int retrievePassWord(){
  return 1;
}

String retrieveUserName(){
  return "user name";
}

void verifyLoginInfo(){
  Py_Initialize();
  PyRun_SimpleFile(f, "verifyAccount.py");
  Py_Finalize();
}

int main(){
  int password = retrievePassWord();
  String username = retrieveUserName();
  verifyLoginInfo(password, username);
  return 0;
}
