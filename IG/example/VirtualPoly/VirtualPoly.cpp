#include <iostream>
using namespace std;

class figure {
protected:
  double x, y;
public:
  void set_dim(double i, double j=0) {
    x = i;
    y = j;
  }
  virtual void show_area() {
    cout << "No area computation defined ";
    cout << "for this class.\n";
  }
} ;

class triangle : public figure {
  public:
    void show_area() {
      cout << "Triangle with height ";
      cout << x << " and base " << y;
      cout << " has an area of ";
      cout << x * 0.5 * y << ".\n";
    }
};

class square : public figure {
  public:
    void show_area() {
      cout << "Square with dimensions ";
      cout << x << "x" << y;
      cout << " has an area of ";
      cout << x *  y << ".\n";
    }
};
class circle : public figure {
  public:
    void show_area() {
      cout << "Circle with radius ";
      cout << x;
      cout << " has an area of ";
      cout << 3.14 * x * x << ".\n";
    }
} ;

int main()
{
  figure *p; // create a pointer to base type

  triangle t; // create objects of derived types
  square s;
  circle c;

  p = &t;
  p->set_dim(10.0, 5.0);
  p->show_area();

  p = &s;
  p->set_dim(10.0, 5.0);
  p->show_area();

  p = &c;
  p->set_dim(9.0);
  p->show_area();

  return 0;
}