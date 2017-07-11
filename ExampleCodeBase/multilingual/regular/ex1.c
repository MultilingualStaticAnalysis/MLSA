#include <python2.7/Python.h>
#include <stdio.h>

int main() {
  FILE *fp;
  Py_Initialize();
  fp = fopen("ex1.py", "r");
  PyRun_SimpleFile(fp, "ex1.py");
  fclose(fp);
  Py_Finalize();
}
