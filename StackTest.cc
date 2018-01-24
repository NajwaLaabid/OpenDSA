#include "AStack.h"
#include <iostream>
#include <sstream>
#include <string>

using namespace std;
static bool success = true;
static int err = 0;
static string msg;

int main (void){

	StackItemType it;
	const int size = 5;
	int res=0;
	AStack * st = new AStack(size);

	int a = 20, b = 25, c = 23;
	st->push(a);
	st->push(b);
	st->push(c);

	// test toString
	string stackString = st->toString();
	if (stackString != "< 23 25 20 >") {
		success = false; 
		err++;
		cout << "Problem with output of toString." << endl;
	}

	// Elm popped: expected: 23
	int output = st->pop();
	if (output != 23) {
		success = false;
		err++;
		cout << "Wrong output. Expected value is 23. Outputed value is " << output;
	}

	st->clear();

	// length after clear should be 0
	if (st->length() != 0) {
		success = false;
		err++;
		cout << "Problem with clear. Length of string different than expected." << endl;
	}


	//general feedback
	if (success != true) 
		cout << endl << "There are " << err << " errors in your code. Specific feedback has been given for each error." << endl;
	else
		cout << "Successful code." << endl;
	
	return 0;
}