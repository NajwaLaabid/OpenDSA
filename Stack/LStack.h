#include "Stack.h"
#include "../List/Link.h"
/* *** ODSATag: LStack1 *** */
// Linked stack implementation
class LStack: public Stack {
  Link* top;               // Pointer to first element
  int size;               // Number of elements

public:
  // Constructors
  LStack() { top = NULL; size = 0; }
  LStack(int size) { top = NULL; size = 0; }
/* *** ODSAendTag: LStack1 *** */

  string toString() {
    string out;
    for (Link* temp = top; temp != NULL;  temp = temp->next()) {
      out.append( to_string( temp->element() ) );
      out.append(" ");
    }
    return out;
  }
/* *** ODSATag: LStack2 *** */

  // Reinitialize stack
  void clear() { top = NULL; size = 0; }

// Put "it" on stack
/* *** ODSATag: LStackPush *** */  
  bool push(const StackItemType& it) {  
    top = new Link(it, top);
    size++;
    return true;
  }
/* *** ODSAendTag: LStackPush *** */

// Remove "it" from stack
/* *** ODSATag: LStackPop *** */    
  StackItemType pop() {           
    if (top == NULL) return -1;
    StackItemType it = top->element();
    top = top->next();
    size--;
    return it;
  }
/* *** ODSAendTag: LStackPop *** */

  StackItemType topValue() {      // Return top value
    if (top == NULL) return -1;
    return top->element();
  }

  // Return stack length
  int length() { return size; }

  // Check if the stack is empty
  bool isEmpty() { return size == 0; }
};
/* *** ODSAendTag: LStack2 *** */