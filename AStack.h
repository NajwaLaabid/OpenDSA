/* Stack - ADT Array Implementation*/
#include "Stack.h"
#include <iostream>
#include <string>

using namespace std;

/*OpenDSATag: Stack - array implementation*/

class AStack : public Stack{
  	StackItemType stackArray[MAX_SIZE];  //Array holding stack elements
  	const int stack_size = MAX_SIZE;
  	int top;   //Current number of stack items
  public: 

  	//constructor: initializes stack_size of stack
  	AStack(int size) : stack_size(size), top(0){
  		for(int i = 0; i < stack_size; i++) stackArray[i] = 0;
  	}

    //default constructor: create stack in MAX_SIZE
    AStack() : stack_size(MAX_SIZE){ 
      for(int i = 0; i < stack_size; i++) stackArray[i] = 0;
    }

    //Checks if stack is empty
    bool isEmpty() { return !top; } 

    //Empties stack
  	void clear() { top = 0; }

    //Returns the stack in a string form
    string toString(){
      string str = "< ";
      for(int i = top-1; i >= 0; i--) str = str + to_string(stackArray[i]) + " ";
      str = str + ">";

      return str;
    }
  
    //Adds element to stack
  	bool push(const StackItemType& newItem){
      if(top == stack_size) return 0; //stack full, cannot push
  		else {
  			stackArray[top++] = newItem;
  			return 1; //push successful
  		}
  	}

    //Returns top element in stack and deletes it afterwards
  	StackItemType pop(){ 
      if(!isEmpty()) return stackArray[--top];
      else return (StackItemType) -1;
    } 

    //Returns top element (without deleting it)
  	StackItemType topValue(){ return stackArray[top-1]; } 

    //Returns current length of stack
  	int length(){ return top; } 
};

/*OpenDSAendTag: Stack - array implementation*/