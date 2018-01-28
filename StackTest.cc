#include "AStack.h"
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
static bool success = true;
static int err = 0;
// SHL: msg, it and res are not used but I assume will be in future.

void generalFeedback(bool success){
	if (success != true) 
		cout << endl << "There are " << err << " errors in your code. Specific feedback has been given for each error." << endl;
	else
		cout << "Successful code." << endl;
}
/* Creates stack and list, both of size SIZE,
   with sync dummy values */
void createStack(AStack* st, int* tester_v, int SIZE){

	for(int i = 0; i < SIZE; i++){
		// push in stack
		st->push(i);
		//cout << "in create : " << st->topValue() << endl;

		// add to vector
		tester_v[i] = i;
	}
}

int main (void){

	StackItemType it;
	const int SIZE = 100;
	int res=0;
	AStack * st = new AStack(SIZE);
	int tester_v[SIZE];

	/* SHL: I would place in a list so it is easier to compare. I believe std::vector is the normal choice in C++ but
	 * deque or list may be easier.
	 * I would create a function that does the add to both so they must stay in sync.
	 * I would uses automatic values and fill the stack to size. For example, you could use index + 100 and then loop to do this.
	 */

	/*Naj: function create Stack added to create stack + list in sync.
	 * I guess the point is to see if the stack is filled as predicted?
	 */

	createStack(st, tester_v, SIZE);

	// compare content of tester_v and stack 
	// to see if push works fine
	// used to test pop at the same time
	int popped;
	for (int i = SIZE - 1; i >= 0; i--){
		popped = st->pop();
		if ( popped != tester_v[i] ) {
			success = false;
			err++;
			cout << "Unmatching values in tester and stack. Stack value: " << popped << ". Vector value: " << tester_v[i] << endl;
			break; // stop at first problem
		}
	}

	// reinitialize stack
	createStack(st, tester_v, SIZE);

	// test toString
	// SHL: Try creating a loop that converted the vector/deque/list to a string to compare to what you get from toString().
	// Naj: done
	string stackString = st->toString();
	string vectorString = "< ";
	//toString for vector values
	for (int i = SIZE-1; i >= 0; i--) {
		vectorString.append(to_string(tester_v[i]));
		vectorString.append(" ");
	}
	vectorString.append(">");

	if (stackString.compare(vectorString) != 0) {
		success = false; 
		err++;
		// SHL: It is best to tell what you got and what you expected so finding the bug is easier.
		// Naj: done
		cout << "Problem with output of toString." << endl;
		cout << "stackString: " << stackString << endl;
		cout << "vectorString: " << vectorString << endl;
	}

	// SHL: Generalize this by using a loop to check all values in stack by poping one at a time.
	// Naj: done
	
	/*
	* SHL: As you add more tests, you need to try all possibilities. For example, what happens when you pop from an empty stack after clear,
	* can you correctly add more values, ...
	*/

	// SHL: These are good start of tests but will need to try all cases such is the stack correct after constructor, can you push and pop
	// multiple times, ... Try to think how to do this in a general way and reuse code for these operations. I can help if you want.

	// SHL: Make into a method so can reuse and is encapsulated.
	// Naj: done
	//general feedback
	// generalFeedback(success);

	return 0;
}
