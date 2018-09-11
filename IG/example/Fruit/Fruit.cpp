// simple list program using inheritance

// Fruit is a base class with 3 derived classes: Apple, Orange, and Grape.
// All child classes inherit all members of the parent class, so Apple,
// Orange, and Grape all have an owner and because print is pure virtual,
// the child classes must define a print routine. The print routine must
// have an identical signature in parent and child classes.

#include <string>
#include <iostream>
using namespace std;

// ----- CLASS Fruit -- the print is virtual ---------------------------------
class Fruit {
protected:
    string owner;
public:
    Fruit(string name) { owner = name; }
    virtual void print() const = 0;          // the "= 0" makes it pure virtual
};

// ----- DERIVED CLASS Apple -------------------------------------------------
class Apple : public Fruit {
public:
    // Apple constructor calls the base class Fruit constructor
    Apple(string name) : Fruit(name) {}
    virtual void print() const { cout << owner << "'s apple" << endl; }
};

// ----- DERIVED CLASS Orange -- has extra member ----------------------------
class Orange : public Fruit {
private:
    string thing;
public:
    // Orange constructor calls the base class Fruit constructor,
    // then initializes its other data member.
    Orange(string name, string kind) : Fruit(name) { thing = kind; }
    virtual void print() const {cout << owner << "'s orange " << thing << endl;}
};

// ----- DERIVED CLASS Grape -------------------------------------------------
class Grape : public Fruit {
public:
    Grape(string name) : Fruit(name) {}
    virtual void print() const { cout << owner << "'s grape" << endl; }
};

// ----- CLASS List ----------------------------------------------------------
class List {
private:
    struct Node {
       Node(Fruit* aFruit) {fruitPtr = aFruit; next = NULL; }
       Fruit* fruitPtr;                  // pointer to the data 
       Node* next;                                   
    };
    Node *head, *tail;

public:
    List(Fruit* aFruit) {head = tail = new Node(aFruit); }

    ~List() {
        while (head != NULL){             // traverse list deallocating memory
           Node* save = head;
           head = head->next;
           delete save->fruitPtr;  save->fruitPtr = NULL;
           delete save;  save = NULL;
        }
        tail = NULL;
     }
        
    void append(Fruit* aFruit) {          // append at end of list
       tail->next = new Node(aFruit);                             
       tail = tail->next;
    }
        
    void printList() {                    // traverse list printing
       for (Node* p = head; p != NULL; p = p->next)
          p->fruitPtr->print();
    }
};
                
// ------------------------------ main ---------------------------------------
int main() {
    // the Apple pointer is cast to a Fruit pointer in the List constructor
    List myList(new Apple("Tom"));

    // similarly the Grape and Orange pointers are cast to Fruit* in append
    myList.append(new Grape("Steve"));
    myList.append(new Orange("Lori","juice"));
    myList.printList(); 
    cout << endl;
    return 0;
}
