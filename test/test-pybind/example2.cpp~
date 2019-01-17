#include <pybind11/pybind11.h>

//int add(int a,int b);
//int subt(int i,int j);
//int cube(int i);
//int square(int j);



int power3(int i){
return i*i*i;
}
int subt(int i, int j) {
    power3(i);
}


int power2(int j){
return j*j;
}

int add(int a, int b = 20) {
int x;
if((a%2)==0){
   x = a + b;
   return x;
}
else{
   power3(a);
   power2(a);
}
  }
   


namespace py = pybind11;

PYBIND11_MODULE(example2, m) {
    // optional module docstring
    m.doc() = "pybind11 example plugin";

    // define add function
    m.def("add", &add, "A function which adds two numbers");
    m.def("subt", &subt, "A function which subtracts two numbers");

}

