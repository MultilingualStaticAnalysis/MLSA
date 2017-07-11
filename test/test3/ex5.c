#include <stdio.h>
#include <python2.7/Python.h>

int main(int argc, char *argv[])
{

  FILE* fp;

  PyObject *my_dict, *my_module;

  Py_Initialize();

  my_dict = PyDict_New();

  PyDict_SetItemString(my_dict, "key1", Py_BuildValue("s", "this is a string"));

  PyDict_SetItemString(my_dict, "key2", Py_BuildValue("i", 13));

  PyDict_SetItemString(my_dict, "key3", Py_BuildValue("(is)", 13, "this is a string"));

  my_module = PyImport_AddModule("my_module");

  PyModule_AddObject(my_module, "my_dict", my_dict);

  fp = fopen("ex4.py", "r");

  PyRun_SimpleFile(fp, "ex5.py");

  Py_Finalize();

  return 0;

}
