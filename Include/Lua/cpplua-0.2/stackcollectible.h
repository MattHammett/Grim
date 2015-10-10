#ifndef STACK_COLLECTIBLE_H
#define STACK_COLLECTIBLE_H

#ifdef STACK_COLLECTIBLE_DEBUG
#include <iostream>

using namespace std;
#endif // STACK_COLLECTIBLE_DEBUG

class StackCollectible {
private:
  static StackCollectible* current;
  StackCollectible* next;
  StackCollectible* previous;
public:
  StackCollectible() {
#ifdef STACK_COLLECTIBLE_DEBUG
    std::cout << "inside StackCollectible constructor" << endl;
#endif
    if (current) current->next = this;
    
    previous = current;
    next = 0;
    current = this;
  }
  virtual ~StackCollectible() {
#ifdef STACK_COLLECTIBLE_DEBUG
    std::cout << "inside StackCollectible destructor" << endl;
#endif
    delete next;
    current = previous;
    
    if (current) current->next = 0;
  }
protected:
  static StackCollectible* getCurrentObject() {
    return current;
  }
};

#define stack_collectible_class(X) class X : public StackCollectible
#define DEFINE_ACCESSOR(X,name) static X* name() { return dynamic_cast<X*>(getCurrentObject()); }

#endif // STACK_COLLECTIBLE_H
