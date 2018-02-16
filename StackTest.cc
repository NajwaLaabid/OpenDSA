#include "AStack.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;
static bool success = true;
static int err = 0;
// SHL: msg, it and res are not used but I assume will be in future.

void signalError(string errorText, ofstream* errorLog ){
	if (errorLog == "NULL") 
		cout << test << endl;
	else
		errorLog << test << endl;
}

void generalFeedback(bool success){
	if (success != true) 
		errorLog << endl << "There are " << err << " errors in your code. Specific feedback has been given for each error." << endl;
	else
		errorLog << "Successful code." << endl;
}
/* Creates stack and list, both of size SIZE,
   with sync dummy values */
void createStack(AStack* st, int* tester_v, int SIZE){

	for(int i = 0; i < SIZE; i++){
		// push in stack
		st->push(i + 100);
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
	ofstream errorLog;

	errorLog.open ("errorLog.txt");

	/* Basic testing of all functions */

	createStack(st, tester_v, SIZE);

	// compare content of tester_v and stack 
	// to see if push works fine
	// used to test pop at the same time
	int popped;
	string errorText;
	for (int i = SIZE - 1; i >= 0; i--){
		popped = st->pop();
		if ( popped != tester_v[i] ) {
			success = false;
			err++;
			// report individual error
			errorText.clear();
			errorText.append("Unmatching values in tester and stack. Stack value: ");
			errorText.append(to_string(popped)); 
			errorText.append(". Vector value: ");
			errorText.append(to_string(tester_v[i]));
			errorText.append(endl);	
			signalError(errorText, &errorLog);
		}
	}

	// reinitialize stack
	createStack(st, tester_v, SIZE);

	// test toString
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
		errorText.clear();
		errorText.append("Problem with output of toString.");
		errorText.append(endl);
		errorText.append("stackString: ");
		errorText.append(stackString);
		errorText.append(endl);
		errorText.append("vectorString: ");
		errorText.append(vectorString); 
		errorText.append(endl);
		signalError(errorText, &errorLog);
	}

	// testing clear: supposed to empty stack by setting its top to 0
	st->clear();

	if(!st->isempty()){
		errorText.clear();
		errorText.append("Stack not empty after clear."); 
		errorText.append(endl);
		signalError(errorText, &errorLog);
	}

	if(st->length()){
		errorText.clear();
		errorText.append("Length not 0 after clear."); 
		errorText.append(endl);
		signalError(errorText, &errorLog);
	}

	/* trying special cases */
	// case 1: turning an empty stack into string
	if(st->tostring() != "< empty >"){
		errorText.clear();
		errorText.append("tostring returned value other than < empty >."); 
		errorText.append(endl);
		signalError(errorText, &errorLog);
	}

	// case 2: get top value of empty stack
	if(st->topValue() != -1){
		errorText.clear();
		errorText.append("top value of empty string is different than default : " + to_string(-1) + "."); 
		errorText.append(endl);
		signalError(errorText, &errorLog);
	}

	// case 3: pop when stack is empty
	int popped = st->pop(); 
	if(popped != -1){
		errorText.clear();
		errorText.append("Stack pop returned something other than -1. Popped value:  " + to_string(popped) + ". Stack current top value: " + to_string(3) + "."); 
		errorText.append(endl);
		signalError(errorText, &errorLog);
	}

	// case 4: push after stack is empty
	st->push(3); // dummy value
	if(st->topvalue() != 3){
		errorText.clear();
		errorText.append("Problem with push after empty. Pushed value:  " + to_string(3) + ". Stack current top value: " + to_string(3) + "."); 
		errorText.append(endl);
		signalError(errorText, &errorLog);
	}

	// case 5: push when stack completely full
	
	/*
	* SHL: As you add more tests, you need to try all possibilities. For example, what happens when you pop from an empty stack after clear,
	* can you correctly add more values, ...
	*/

	// SHL: These are good start of tests but will need to try all cases such is the stack correct after constructor, can you push and pop
	// multiple times, ... Try to think how to do this in a general way and reuse code for these operations. I can help if you want.

	//general feedback

	generalFeedback(success);
	errorLog.close();
	return 0;
}
