/*
  * Stack ADT - general implementation
*/

//passing new item as a reference (not a pointer, not copying value)
//copying might be expensive, pass object instead
//const is used to make sure newItem is not modified in function body
// =0 operator makes class abstract: cannot instantiate from it
//compiler complains about undefined reference to Vtable in Stack when removing =0
//virtual means class is polymorphic:
  // can create many inheriting classes & use Stack as a general one 
  // functions can be overriden in derived classes


#ifndef STACK_H //checks if STACK_H declared before including header file
#define STACK_H
#include <string>

using namespace std;

const int MAX_SIZE = 10;

typedef int StackItemType;
/* OpenDSATag: StackADT*/
class Stack { //class stack ADT
public: 
  //Empties the stack
  virtual void clear()=0; 

  //Checks if stack isEmpty
  virtual bool isEmpty()=0;

  //Transforms stack to string
  virtual string toString()=0;

  //Pushes a new item onto stack. Returns a boolean (1 = successful, 0 = error)
  virtual bool push(const StackItemType& newItem)=0;  

  //Removes and returns first element in stack
  virtual StackItemType pop()=0; 

  //Returns a copy of the first element in stack
  virtual StackItemType topValue()=0; 

  //Returns length of stack
  virtual int length()=0; 
};
  
/*OpenDSAEndTag: StackADT*/

#endif
