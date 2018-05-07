#include "AStack.h"
#include "LStack.h"
#include "../ErrorRec.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <typeinfo>

using namespace std;

/* Class used to automatically test the structure Stack.
 * Current testing strategy:
 	* Three main functions: 
 		* One for initialization : run()
 		* One for functions to be tested on an empty stack: checkEmpty()
 		* One for all functions implemented in the ADT: check()
 	* Functions in play (testing schema):
 		* Run() initializes custom ADT and built-in ADT
 		* Call checkEmpty() on empty ADT
 		* Insert elements in ADT and call check() on every insert
*/

class StackTest {
	public :

		// The number of items stored in stack during the test
		const int TEST_SIZE = 100;
		// True if you want to create a text file to record errors
		bool useFile = true;
		// Instance of ErrorRec class which holds the number of errors and prints
		// out error messages
		ErrorRec* record;
		// built-in structure
		vector<StackItemType> tester_v;
		// auxiliary vector, used in function check()
		vector<StackItemType> temp;
		// custom ADT
		Stack* st;

		StackTest(bool value){
			useFile = value;
		}

		void run( Stack* stack, string className ) {
			// empty vectors from potential previous runs
			temp.clear();
			tester_v.clear();

			// initialize a new file for every run of the function
			// (probably testing a new class)
			record = new ErrorRec( useFile, className );

			// initialize custom stack
			st = stack;

			// first round of tests: on an empty stack
			checkEmpty();

			// second round of tests: run all functions on every addition
			for(int i = 0; i < TEST_SIZE; i++) 
				check(100 + i);

			// output general feedback: success/ error message
			record->feedback();
		}

		void checkEmpty() {
			// length(): returns number of elements in stack.
			if (st->length() != 0) 
				record->printError("length() returns value other than 0 after init. Value returned:"+ to_string(st->length()));
			
			// isEmpty(): returns 1 if stack is empty, 0 otherwise
			if (st->isEmpty() != true) 
				record->printError("isEmpty() returns " + to_string(st->isEmpty()) + " after init.");

			// topValue(): returns top of stack
			if (st->topValue() != -1) 
				record->printError("topValue() returns value other than -1 after init. Value returned: " + to_string(st->topValue()));

			// pop(): removes and returns top value of stack.
			StackItemType popped = st->pop();
			if (popped != -1) 
				record->printError("pop() returned value other than -1 after init. Value returned: " + to_string(popped));

			// toString(): returns stack content parsed in string format
			if (st->toString() != "")
				record->printError("toString() returns value other than '' after init. Value returned: " + st->toString());

			// clear(): empties stack. No returned value.
			st->clear();
		
			// check length after clear
			if (st->length() != 0) 
				record->printError("length() returned value other than 0 after running clear (testing empty stack). Value returned: " + to_string(st->length()));		
		
		}

		void check(StackItemType item){
			
			// Add the item to both stacks
			st->push(item);
			tester_v.push_back(item);

			//cmp length to size of tester_v
			if (st->length() != tester_v.size()) 
				record->printError("length() of stack: " + to_string(st->length())
					+ ". Length expected: " + to_string(tester_v.size()));
			
			// check isEmpty
			if (st->isEmpty() != false)
				record->printError("isEmpty() returns " + to_string(st->isEmpty()) + " in normally-filled stack. Expected value: false.");

			// check topValue
			if ( st->topValue() != tester_v.back() ) 
				record->printError("Unexpected topValue() in normally-filled stack. topValue: " + to_string(st->topValue()) + ". Expected top value: " + to_string(tester_v.back()));

			// check toString
			if ( st->toString() != toString(tester_v) ) 
				record->printError( "Unexpeted toString() value. toString returned: " + st->toString() + ". Tester_v: "+ toString(tester_v) );
			
			/* Memory problem */
			
			/*
				StackItemType st_popped;
				StackItemType tv_popped;
				
				int curSize = st->length();
				
				// cout << st->length() << endl;
				for(int i = 0; i < curSize; i++) {
					st_popped = st->pop();
					tv_popped = tester_v.back();
					if (st_popped != tv_popped) 
						record->printError( "Class: " + className + ". In check: stack pop different than tester_v pop. Stack pop: " + to_string(st_popped) + ". Tester_v pop: " + to_string(tv_popped) );
					
					tester_v.pop_back();
					temp.push_back( st_popped );
				}
				
				//Restore values
				for(int i = 0; i < curSize; i++) {

					st->push(temp.back());
					temp.pop_back();
				}

				temp.clear();
			*/
		}

		//converts the test stack to string following the expected string format of AStack
		string toString(vector<StackItemType> tester_v) {
			string str = "";
		    for (int i = tester_v.size()-1; i >= 0; i--) str = str + to_string(tester_v[i]) + " ";
		
		    return str;
		}
};

int main(void){
	// true when want to use log files
	// false when prefer to print to screen
	bool useFile = true; 
	// instatiating testing class
	StackTest test = StackTest(useFile);

	int size = 100;

	// Testing array implementation of stack
	AStack * aSt = new AStack(size);
	AStack * aSt_default = new AStack();

	test.run(aSt, "AStack");
	test.run(aSt_default, "AStack_default");

	// Testing linked list implementation of stack
	LStack* lSt = new LStack();

	test.run(lSt, "LStack");
	
	return 0;
}
