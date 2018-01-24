#include "AStack.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
static bool success = true;
static int err = 0;
// SHL: msg, it and res are not used but I assume will be in future.
static string msg;

int main (void){

	StackItemType it;
	// SHL: I believe convention is const variable names are UPPERCASE.
	const int size = 5;
	int res=0;
	AStack * st = new AStack(size);

	/* SHL: I would place in a list so it is easier to compare. I believe std::vector is the normal choice in C++ but
	 * deque or list may be easier.
	 * I would create a function that does the add to both so they must stay in sync.
	 * I would uses automatic values and fill the stack to size. For example, you could use index + 100 and then loop to do this.
	 */
	int a = 20, b = 25, c = 23;
	st->push(a);
	st->push(b);
	st->push(c);

	// test toString
	// SHL: Try creating a loop that converted the vector/deque/list to a string to compare to what you get from toString().
	string stackString = st->toString();
	if (stackString != "< 23 25 20 >") {
		success = false; 
		err++;
		// SHL: It is best to tell what you got and what you expected so finding the bug is easier.
		cout << "Problem with output of toString." << endl;
	}

	// Elm popped: expected: 23
	// SHL: Generalize this by using a loop to check all values in stack by poping one at a time.
	int output = st->pop();
	if (output != 23) {
		success = false;
		err++;
		cout << "Wrong output. Expected value is 23. Outputed value is " << output;
	}

	st->clear();

	// Others are does an ea
	// length after clear should be 0
	if (st->length() != 0) {
		success = false;
		err++;
		cout << "Problem with clear. Length of string different than expected." << endl;
	}

	/*
	* SHL: As you add more tests, you need to try all possibilities. For example, what happens when you pop from an empty stack after clear,
	* can you correctly add more values, ...
	*/

	// SHL: These are good start of tests but will need to try all cases such is the stack correct after constructor, can you push and pop
	// multiple times, ... Try to think how to do this in a general way and reuse code for these operations. I can help if you want.

	// SHL: Make into a method so can reuse and is encapsulated.
	//general feedback
	if (success != true) 
		cout << endl << "There are " << err << " errors in your code. Specific feedback has been given for each error." << endl;
	else
		cout << "Successful code." << endl;
	
	return 0;
}
