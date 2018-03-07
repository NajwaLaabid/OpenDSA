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
  	const int STACK_SIZE; // Current number of list items
  	int top; // Position of top element of stack
    /* *** ODSAendTag: AStackVars *** */

  public: 

  	// Constructor
    // Create a new stack element of size "size" 
  	AStack(int size) : STACK_SIZE(size), top(0) {
  		// Initialize the array
      top = 0;
      for (int i = 0; i < STACK_SIZE; i++) stackArray[i] = 0;
  	} // End constructor

    // Default constructor
    // Create stack in MAX_SIZE
    AStack() : STACK_SIZE(MAX_SIZE) {
      // Initialize the array
      top = 0;
      for (int i = 0; i < STACK_SIZE; i++) stackArray[i] = 0;
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
      string str = "";
      for (int i = top-1; i >= 0; i--) str = str + to_string(stackArray[i]) + " ";
      return str;
    }
  
    /* *** ODSATag: AStackPush *** */
    // Adds newItem to stack
  	bool push(const StackItemType& newItem) {
      if (top == STACK_SIZE) return false; // Stack full, cannot push
  		else {
  			stackArray[top++] = newItem;
  			return true; // Push successful
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
  	StackItemType topValue() { 
      if (top == 0)
        return -1;
      else
        return stackArray[top-1]; } 

    //Returns current length of stack
  	int length() { return top; } 

    //Destructor: required for polymorphism
    ~ AStack () = default;
    /* *** OpenDSAendTag: AStack *** */

};
