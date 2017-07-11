#include <iostream>  
#include <python2.7/Python.h>  

using namespace std;  
int main()  
{  
    Py_Initialize();  
    FILE *fp = fopen("ex3.py", "r");  
    if(fp != NULL) {  
        PyRun_SimpleFile(fp, "ex3.py");  
        fclose(fp);  
    }  
    Py_Finalize();  
    cout << "Hello! Return to C++ World!" << endl;  
    return 0;  
}  
