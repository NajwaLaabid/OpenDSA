#include "Stack.h"
#include <iostream>
#include <string>

using namespace std;

/* *** ODSATag: AStack *** */ 
// Array-based stack implementation
/* *** ODSATag: AStackVars *** */
// TODO SHL Eclipse gives warning (not sure why): AStack has virtual method length but non-virtual destructor
class AStack : public Stack{
  	StackItemType stackArray[MAX_SIZE]; // Array holding stack elements
  	// TODO SHL Eclipse gives: warning: in-class initialization of non-static data member is a C++11 extension [-Wc++11-extensions]
  	const int stack_size = MAX_SIZE; // Current number of list items
  	int top; // Position of top element of stack
    /* *** ODSAendTag: AStackVars *** */

  public: 

  	// Constructor
    // Create a new stack element of size "size" 
  	AStack(int size) : stack_size(size), top(0) {
  		// Initialize the array
      for (int i = 0; i < stack_size; i++) stackArray[i] = 0;
  	} // End constructor

    // Default constructor
    // Create stack in MAX_SIZE
  	// SHL Eclipse gives warning that top not initialized in this constructor
    AStack() : stack_size(MAX_SIZE) {
      // Initialize the array
      for (int i = 0; i < stack_size; i++) stackArray[i] = 0;
    }// End default constructor

    // Checks if stack is empty
    bool isEmpty() { 
      return !top; 
    } 

    // Reinitializes stack
  	void clear() { 
      top = 0;   // Simply reinitialize top
    }

    // Returns the stack in a string form
    string toString() {
      string str = "< ";
      for (int i = top-1; i >= 0; i--) str = str + to_string(stackArray[i]) + " ";
      str = str + ">";
      return str;
    }
  
    /* *** ODSATag: AStackPush *** */
    // Adds newItem to stack
  	bool push(const StackItemType& newItem) {
      if (top == stack_size) return 0; // Stack full, cannot push
  		else {
  			stackArray[top++] = newItem;
  			return 1; // Push successful
  		}
  	}
    /* *** ODSAendTag: AStackPush *** */

    /* *** ODSATag: AStackPop *** */
    //Returns top element in stack and deletes it afterwards
  	StackItemType pop() { 
      if (!isEmpty()) return stackArray[--top];
      else return (StackItemType) -1;
    } 
    /* *** ODSAendTag: AStackPush *** */

    //Returns top element (without deleting it)
  	StackItemType topValue() { return stackArray[top-1]; } 

    //Returns current length of stack
  	int length() { return top; } 
  	// TODO should this be AStack for closing tag to match open one?
    /* *** OpenDSAendTag: Atack *** */

};
