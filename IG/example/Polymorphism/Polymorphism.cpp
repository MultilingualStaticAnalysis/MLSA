#include <iostream>
#include <cstring>
using namespace std;

class B_class {
  char author[80];
public:
  void put_author(char *s) { strcpy(author, s); }
  void show_author() { cout << author << "\n"; }
} ;

class D_class : public B_class {
  char title[80];
public:
  void put_title(char *num) {
    strcpy(title, num);
  }
  void show_title() {
    cout << "Title: ";
    cout <<  title << "\n";
  }
};

int main()
{
  B_class *p;
  B_class B_ob;

  D_class *dp;
  D_class D_ob;

  p = &B_ob;  // address of base

  // Access B_class via pointer.
  p->put_author("Tom Clancy");

  // Access D_class via base pointer.
  p = &D_ob;
  p->put_author("William Shakespeare");

  // Show that each author went into proper object.
  B_ob.show_author();
  D_ob.show_author();
  cout << "\n";

  /* Since put_title() and show_title() are not part
     of the base class, they are not accessible via
     the base pointer p and must be accessed either
     directly, or, as shown here, through a pointer to the
     derived type.
  */
  dp = &D_ob;
  dp->put_title("The Tempest");
  p->show_author(); // either p or dp can be used here.
  dp->show_title( );

  return 0;
}