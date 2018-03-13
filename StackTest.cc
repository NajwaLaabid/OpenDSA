#include "AStack.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

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
		const string fileName = "errorLog.txt";
		ofstream errorLog;

	public :

		// Instantiating custom stack
		static const int SIZE = 100;
		static const int MAX_SIZE = 1000;

		AStackTest(bool useFile){
			if (useFile == true) {
				errorLog.open(fileName);
			}
		}

		/* Used to run test cases */
		void run(){
			/* State 1: empty stack after init */

			// length(): returns number of elements in AStack.
			int len = st->length();
			if (len != 0) {
				error("length() returns value other than 0 after init. Value returned:"+ to_string(len));
			}

			// isEmpty(): returns 1 if AStack is empty, 0 otherwise
			bool isempty = st->isEmpty();
			if (isempty != true) {
				error("isEmpty() returns " + to_string(isempty) + " after init.");
			}

			// topValue(): returns top of AStack
			StackItemType topvalue = st->topValue();
			if (topvalue != -1) {
				error("topValue() returns value other than -1 after init. Value returned: " + to_string(topvalue));
			}

			// toString(): returns AStack content parsed in string format
			string tostring = st->toString();
			if (tostring != "") {
				error("toString() returns value other than '' after init. Value returned: " + tostring);
			}

			// clear(): empties AStack. No returned value.
			st->clear();
			len = st->length();
			if (len != 0) {
				error("length() returned value other than 0 after running clear (init testing). Value returned: " + to_string(len));
			}
			// pop(): removes and returns top value of AStack.
			StackItemType popped = st->pop();
			if (popped != -1) {
				error("pop() returned value other than -1 after init. Value returned: " + to_string(popped));
			}
			// push(): adds a StackItemType to the top of AStack. 
			bool push_return = st->push(dummy);
			if (push_return != true) {
				error("push() returned value other than 'true' after init. Pushing dummy value:" + to_string(dummy) +". Value returned: " + to_string(push_return));
			}

			// topValue(): see above
			topvalue = st->topValue();
			if (topvalue != dummy){
				error("Unexpected topValue in stack (init test, pushing dummy). topValue: " + to_string(topvalue) + ". Expected dummy value: " + to_string(dummy));
			}

			// clear dummy value
			st->clear();

			/* State 2: normally-filled stack */
			fillStack(st, &tester_v, SIZE);

			// cmp length to size of tester_v
			int testersize = tester_v.size();
			len = st->length();
			if (len != testersize) {
				error("length() returns value different than size of tester_v. Length of stack: " + to_string(len) + " Size of tester_v: " + to_string(testersize) + "\n\n");
			}

			// cmp length to expected size of tester_v
			len = st->length();
			if (len != SIZE) {
				error("length() returns value different than SIZE. Length of stack: " + to_string(len) + " SIZE: " + to_string(SIZE));
			}

			// check isEmpty
			isempty = st->isEmpty();
			if (isempty != false) {
				error("isEmpty() returns " + to_string(isempty) + " in normally-filled stack. Expected value: false.");
			}

			// check topValue
			StackItemType backvalue = tester_v.back();
			topvalue = st->topValue();
			if (topvalue != backvalue) {
				error("Unexpected topValue() in normally-filled stack. topValue: " + to_string(topvalue) + ". Expected top value: " + to_string(backvalue));
			}

			// check toString
			string stringtester = toString(tester_v);
			tostring = st->toString();
			if ( tostring != stringtester) {
				error("Unexpeted toString() value. toString returned: " + tostring + ". Tester_v: "+ stringtester);
			}

			// check(): pops and checks all values of stack
			check(st, tester_v, SIZE);

			// check if tester_v and stack still have same size  
			testersize = tester_v.size();
			len = st->length();
			if (testersize != len){
				error("Stack and tester_v do not have the same length after check. Size of tester: " + to_string(testersize) + ". Size of stack: " + to_string(len));
			}

			// make sure tester_v is empty
			tester_v.clear();

			/* State 3: overly-filled stack */
			fillStack(st, &tester_v, SIZE);

			// push in a full stack
			push_return = st->push(dummy);
			if (push_return != 0){
				error("Pushed in an overly-filled stack.");
			}

			/* State 4: Special cases */
			st->clear();

			/* Testing default constructor */
			fillStack(st_default, &tester_v, MAX_SIZE);

			// check length
			len = st_default->length();
			if (len != MAX_SIZE) {
				error("Unexpected length of st_default. Length of st_default: " + to_string(len) + ". Expected length: " + to_string(MAX_SIZE));
			}
			// pop and check all values of Stack
			check(st_default, tester_v, MAX_SIZE);

			// generalFeedback(): says if code is successful or not.
			generalFeedback(err);
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
					error("In check: stack pop different than tester_v pop. Stack pop: " + to_string(st_popped) + ". Tester_v pop: " + to_string(tv_popped));
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

		// error(): prints every error to logfile / screen
		void error(string text) {
			err++;
			if ( !errorLog.is_open() ) 
				cout << text << "\n\n";
			else
				errorLog << text << "\n\n";
		}

		// initialize the test stack
		void fillStack(AStack* st, vector<StackItemType>* tester_v, int SIZE){
			for(StackItemType i = 0; i < SIZE; i++){
				st->push(i + 100);
				tester_v->push_back(i + 100);
			}
		}

		// tells if code was successful or not depending on the value of err
		void generalFeedback(int err){
			if (err != 0) 
				cout << "There are " << err << " errors in your code. You can find specific feedback in errorLog file if you chose to output to a file." << endl;
			else
				cout << "Successful code." << endl;
		}
};

int main(void){
	bool useFile = true;
	AStackTest test = AStackTest(useFile);

	test.run();
	
	return 0;
}
