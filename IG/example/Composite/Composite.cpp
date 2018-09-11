#include <vector>
#include <iostream> // std::cout
#include <memory> // std::auto_ptr
#include <algorithm> // std::for_each
using namespace std;
 
class Graphic
{
public:
  virtual void print() const = 0;
  virtual ~Graphic() {}
};
 
class Ellipse : public Graphic
{
public:
  void print() const {
    cout << "Ellipse \n";
  }
};
 
class CompositeGraphic : public Graphic
{
public:
  void print() const {
    for(Graphic * a: graphicList_) {
      a->print();
    }
  }
 
  void add(Graphic *aGraphic) {
    graphicList_.push_back(aGraphic);
  }
 
private:
  vector<Graphic*>  graphicList_;
};
 
int main()
{
  // Initialize four ellipses
  const Ellipse* ellipse1(new Ellipse());
  const Ellipse* ellipse2(new Ellipse());
  const Ellipse* ellipse3(new Ellipse());
  const Ellipse* ellipse4(new Ellipse());
 
  // Initialize three composite graphics
  CompositeGraphic* graphic(new CompositeGraphic());
  CompositeGraphic* graphic1(new CompositeGraphic());
  CompositeGraphic* graphic2(new CompositeGraphic());
 
  // Composes the graphics
  graphic1->add(ellipse1);
  graphic1->add(ellipse2);
  graphic1->add(ellipse3);
 
  graphic2->add(ellipse4);
 
  graphic->add(graphic1);
  graphic->add(graphic2);
 
  // Prints the complete graphic (four times the string "Ellipse")
  graphic->print();
  return 0;
}
