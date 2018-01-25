/* Stack ADT - general implementation
 * January 2018
 */
#ifndef STACK_H
#define STACK_H
#include <string>

using namespace std;

const int MAX_SIZE = 10;
typedef int StackItemType;

/* *** OpenDSATag: StackADT *** */
// TODO SHL Eclipse gives warning (not sure why): Stack has virtual method length but non-virtual destructor
class Stack { // Stack class ADT
public: 
  // Empties the stack
  virtual void clear() =0; 

  // Checks if stack isEmpty
  virtual bool isEmpty() =0;

  // Transforms stack to string
  virtual string toString() =0;

  // Pushes a new item onto stack
  // Returns a boolean (1 = successful, 0 = error)
  virtual bool push(const StackItemType& newItem) =0;  

  // Removes and returns first element in stack
  virtual StackItemType pop() =0; 

  // Returns a copy of the first element in stack
  virtual StackItemType topValue() =0; 

  // Returns length of stack
  virtual int length() =0; 
  /* *** OpenDSAEndTag: StackADT *** */
};

#endif /* AList H */
