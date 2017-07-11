#include "stdio.h"
#include <python2.7/Python.h>

#pragma comment(lib,"python25_d.lib")

int main(int argc, _TCHAR* argv[])
{
  FILE *fp;
  Py_Initialize();

  fp = fopen("ex2.py", "r");
  if(fp)
  {
    PyRun_SimpleFile(fp, "ex2.py");
    fclose(fp);
  }
  else {
    printf("Can not find	\".py\"	file	 \n");
  }
  Py_Finalize();
  return 0;
}
