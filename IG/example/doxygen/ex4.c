#include <python2.7/Python.h>

#define INPUT_FILE	"ex4.py"

int main()
{
	Py_Initialize();

	FILE *fp = fopen(INPUT_FILE, "rt");
	PyRun_SimpleFile(fp, INPUT_FILE);

	Py_Finalize();
}
