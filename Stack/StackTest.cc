#include "AStack.h"
#include "LStack.h"
#include "../ErrorRec.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

/* Class used to automatically test the structure AStack */
class AStackTest {
	private:
		// Declare structures to be tested: AStack object
		AStack * st = new AStack(SIZE);
		AStack * st_default = new AStack();

		// Declare testing variable: C++ vector
		vector<StackItemType> tester_v; 

		// Auxiliary variables
		StackItemType dummy = 100; // insert dummy value occasionally in testing 
	 	int err = 0; // counts errors found in the code

		// File relevant variables
	 	ErrorRec * record;

	public :

		// Instantiating custom stack
		static const int SIZE = 100;
		static const int MAX_SIZE = 1000;

		AStackTest(bool useFile){
			record = new ErrorRec(useFile, "AStack");
		}

		/* Used to run test cases */
		void run(){
			/* State 1: empty stack after init */

			// length(): returns number of elements in AStack.
			int len = st->length();
			if (len != 0) {
				record->printError("length() returns value other than 0 after init. Value returned:"+ to_string(len));
			}

			// isEmpty(): returns 1 if AStack is empty, 0 otherwise
			bool isempty = st->isEmpty();
			if (isempty != true) {
				record->printError("isEmpty() returns " + to_string(isempty) + " after init.");
			}

			// topValue(): returns top of AStack
			StackItemType topvalue = st->topValue();
			if (topvalue != -1) {
				record->printError("topValue() returns value other than -1 after init. Value returned: " + to_string(topvalue));
			}

			// toString(): returns AStack content parsed in string format
			string tostring = st->toString();
			if (tostring != "") {
				record->printError("toString() returns value other than '' after init. Value returned: " + tostring);
			}

			// clear(): empties AStack. No returned value.
			st->clear();
			len = st->length();
			if (len != 0) {
				record->printError("length() returned value other than 0 after running clear (init testing). Value returned: " + to_string(len));
			}
			// pop(): removes and returns top value of AStack.
			StackItemType popped = st->pop();
			if (popped != -1) {
				record->printError("pop() returned value other than -1 after init. Value returned: " + to_string(popped));
			}
			// push(): adds a StackItemType to the top of AStack. 
			bool push_return = st->push(dummy);
			if (push_return != true) {
				record->printError("push() returned value other than 'true' after init. Pushing dummy value:" + to_string(dummy) +". Value returned: " + to_string(push_return));
			}

			// topValue(): see above
			topvalue = st->topValue();
			if (topvalue != dummy){
				record->printError("Unexpected topValue in stack (init test, pushing dummy). topValue: " + to_string(topvalue) + ". Expected dummy value: " + to_string(dummy));
			}

			// clear dummy value
			st->clear();

			/* State 2: normally-filled stack */
			fillStack(st, &tester_v, SIZE);

			// cmp length to size of tester_v
			int testersize = tester_v.size();
			len = st->length();
			if (len != testersize) {
				record->printError("length() returns value different than size of tester_v. Length of stack: " + to_string(len) + " Size of tester_v: " + to_string(testersize) + "\n\n");
			}

			// cmp length to expected size of tester_v
			len = st->length();
			if (len != SIZE) {
				record->printError("length() returns value different than SIZE. Length of stack: " + to_string(len) + " SIZE: " + to_string(SIZE));
			}

			// check isEmpty
			isempty = st->isEmpty();
			if (isempty != false) {
				record->printError("isEmpty() returns " + to_string(isempty) + " in normally-filled stack. Expected value: false.");
			}

			// check topValue
			StackItemType backvalue = tester_v.back();
			topvalue = st->topValue();
			if (topvalue != backvalue) {
				record->printError("Unexpected topValue() in normally-filled stack. topValue: " + to_string(topvalue) + ". Expected top value: " + to_string(backvalue));
			}

			// check toString
			string stringtester = toString(tester_v);
			tostring = st->toString();
			if ( tostring != stringtester) {
				record->printError("Unexpeted toString() value. toString returned: " + tostring + ". Tester_v: "+ stringtester);
			}

			// check(): pops and checks all values of stack
			check(st, tester_v, SIZE);

			// check if tester_v and stack still have same size  
			testersize = tester_v.size();
			len = st->length();
			if (testersize != len){
				record->printError("Stack and tester_v do not have the same length after check. Size of tester: " + to_string(testersize) + ". Size of stack: " + to_string(len));
			}

			// make sure tester_v is empty
			tester_v.clear();

			/* State 3: overly-filled stack */
			fillStack(st, &tester_v, SIZE);

			// push in a full stack
			push_return = st->push(dummy);
			if (push_return != 0){
				record->printError("Pushed in an overly-filled stack.");
			}

			/* State 4: Special cases */
			st->clear();

			/* Testing default constructor */
			fillStack(st_default, &tester_v, MAX_SIZE);

			// check length
			len = st_default->length();
			if (len != MAX_SIZE) {
				record->printError("Unexpected length of st_default. Length of st_default: " + to_string(len) + ". Expected length: " + to_string(MAX_SIZE));
			}
			// pop and check all values of Stack
			check(st_default, tester_v, MAX_SIZE);

			// generalFeedback(): says if code is successful or not.
			record->feedback();
		}
		
		// check(): pops and checks all values of stack
		void check(AStack* st, vector<StackItemType> tester_v, int SIZE){
			int st_popped;
			int tv_popped;
			vector<StackItemType> temp;
			
			for (int i = SIZE; i > 0; i--){
				st_popped = st->pop();
				tv_popped = tester_v.back();
				if (st_popped != tv_popped) {
					record->printError("In check: stack pop different than tester_v pop. Stack pop: " + to_string(st_popped) + ". Tester_v pop: " + to_string(tv_popped));
				}
				tester_v.pop_back();
				temp.push_back(st_popped);
			}

			//Restore values
			for (int i = SIZE; i > 0; i--){
				st->push(temp.back());
				temp.pop_back();
			}
		}

		//converts the test stack to string following the expected string format of AStack
		string toString(vector<StackItemType> tester_v) {
			string str = "";
		    for (int i = tester_v.size()-1; i >= 0; i--) str = str + to_string(tester_v[i]) + " ";
		
		    return str;
		}

		// initialize the test stack
		void fillStack(AStack* st, vector<StackItemType>* tester_v, int SIZE){
			for(StackItemType i = 0; i < SIZE; i++){
				st->push(i + 100);
				tester_v->push_back(i + 100);
				// SHL: This test is fine but you can see Yuya's code on how I had him test after each push.
			}
		}
};

int main(void){
	// SHL: Some comments here are always nice.
	bool useFile = true;
	AStackTest test = AStackTest(useFile);
	LStack* stack = new LStack();

	stack->clear();

	test.run();
	
	return 0;
}
