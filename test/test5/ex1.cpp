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
  char pyfile[] = "ex1.py";
  FILE* f;
  f = fopen("ex1.py", 
"r");
  Py_Initialize();
  PyRun_SimpleFile(f, pyfile);
  Py_Finalize();
}

int main(){
  int password = retrievePassWord();
  string username = retrieveUserName();
  verifyLoginInfo(password, username);
  return 0;
}
