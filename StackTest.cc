#include "AStack.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

class AStackTest {
	public :

		// instantiating custom stack
		static const int SIZE = 100;
		static const int MAX_SIZE = 1000;
		AStack * st = new AStack(SIZE);
		AStack * st_default = new AStack();

		// instantiating testing structures 
		vector<StackItemType> tester_v; //testing using arrays

		// auxiliary variables
		StackItemType dummy = 100; // should be less than SIZE
		bool success = true;
	 	int err = 0;

		// file relevant code
		ofstream errorLog;

		AStackTest(bool useFile){
			if (useFile == true) {
				errorLog.open ("errorLog.txt");
			}
		}

		void run(){
			/* State 1: empty stack after init */
			// function: length
			if (st->length() != 0) {
				success = false;
				err++;
				error("length() returns value other than 0 after init.\n\n");
			}
			// function: isEmpty
			if (st->isEmpty() != 1) {
				success = false;
				err++;
				error("isEmpty() returns false after init.\n\n");
			}
			// function: topValue
			if (st->topValue() != -1) {
				success = false;
				err++;
				error("topValue() returns value other than -1 after init.\n\n");
			}
			// function: toString
			if (st->toString() != "< empty >") {
				success = false;
				err++;
				error("toString() returns value other than '< empty >' after init.\n\n");
			}
			// function: clear()
			st->clear();
			if (st->length() != 0) {
				success = false;
				err++;
				error("length() returned value other than 0 after running clear (init testing).\n\n");
			}
			// function: pop()
			if (st->pop() != -1) {
				success = false;
				err++;
				error("pop() returned value other than -1 after init.\n\n");
			}
			// function: push()
			if (st->push(dummy) != 1) {
				success = false;
				err++;
				error("push() returned value other than 1 after init. Pushing dummy value:" + to_string(dummy) +"\n\n");
			}
			if (st->topValue() != dummy){
				success = false;
				err++;
				error("Unexpected topValue in stack (init test, pushing dummy). topValue: " + to_string(st->topValue()) + ". Expected dummy value: " + to_string(dummy) + "\n\n");
			}
			// clear dummy value
			st->clear();

			/* State 2: normally-filled stack */
			fillStack(st, &tester_v, SIZE); // push tested inside this function

			// function: length (cmp to size of tester_v)
			if (st->length() != tester_v.size()) {
				success = false;
				err++;
				error("length() returns value different than size of tester_v. Length of stack: " + to_string(st->length()) + " Size of tester_v: " + to_string(tester_v.size()) + "\n\n");
			}
			// function: length (cmp to expected size of tester_v)
			if (st->length() != SIZE) {
				success = false;
				err++;
				error("length() returns value different than SIZE. Length of stack: " + to_string(st->length()) + " SIZE: " + to_string(SIZE) + "\n\n");
			}
			// function: isEmpty
			if (st->isEmpty() != 0) {
				success = false;
				err++;
				error("isEmpty() returns true in normally-filled stack.\n\n");
			}
			// function: topValue
			if (st->topValue() != tester_v.back()) {
				success = false;
				err++;
				error("Unexpected topValue() in normally-filled stack. topValue: " + to_string(st->topValue()) + ". Expected value: " + to_string(tester_v.back()) + ". \n\n");
			}
			// function: toString
			if (st->toString() != toString(tester_v)) {
				success = false;
				err++;
				error("Unexpeted toString() value. toString returned: " + st->toString() + "\n tester_v: "+ toString(tester_v) +"\n\n");
			}
			// function: pop. check all values of stack
			check(st, tester_v, SIZE);
			// check if both tester_v and stack are empty now 
			if (st->isEmpty() != 1){
				success = false;
				err++;
				error("Stack not empty after check.\n\n");
			}

			// make sure tester_v is empty
			tester_v.clear();

			/* State 3: overly-filled stack */
			fillStack(st, &tester_v, SIZE);

			// function : push.
			if (st->push(dummy) != 0){
				success = false;
				err++;
				error("Pushed in an overly-filled stack.\n\n");
			}

			/* State 4: Special cases */
			st->clear();
			// push NULL
			/*if (st->push(NULL) == 1)
				error("Pushed NULL.\n\n");*/
			// push string
			/*if (st->push("Hi") == 1)
				error("Pushed string when data type int.\n\n");*/

			// push biggest int value
			if (st->push(INT_MAX) != 1){
				success = false;
				err++;
				error("Could not push INT_MAX.\n\n");
			}

			// push smallest int value
			if (st->push(INT_MIN) != 1){
				success = false;
				err++;
				error("Could not push INT_MIN.\n\n");
			}

			/* Testing default constructor */
			fillStack(st_default, &tester_v, MAX_SIZE);

			// function: length
			if (st_default->length() != MAX_SIZE) {
				success = false;
				err++;
				error("Unexpected length of st_default. Length of st_default: " + to_string(st_default->length()) + ". Expected length: " + to_string(MAX_SIZE) + "\n\n");
			}
			// global check
			check(st_default, tester_v, MAX_SIZE);

			generalFeedback(success);
		}
		
		void check(AStack* st, vector<StackItemType> tester_v, int SIZE){
			int st_popped;
			int tv_popped;
			for (int i = SIZE; i > 0; i--){
				st_popped = st->pop();
				tv_popped = tester_v.back();
				if (st_popped != tv_popped) {
					success = false;
					err++;
					error("In check: stack pop different than tester_v pop. Stack pop: " + to_string(st_popped) + ". Tester_v pop: " + to_string(tv_popped) + ".\n\n");
				}
				tester_v.pop_back();
			}
		}

		string toString(vector<StackItemType> tester_v) {
			string str = "< ";
		    if (tester_v.size() == 0){
		    	str = str + "empty >";
		    }else{
		    	for (int i = tester_v.size()-1; i >= 0; i--) str = str + to_string(tester_v[i]) + " ";
		        str = str + ">";
		    }
		    
		    return str;
		}

		void error(string text) {
			if ( !errorLog.is_open() ) 
				cout << text;
			else
				errorLog << text;
		}

		void fillStack(AStack* st, vector<StackItemType>* tester_v, int SIZE){
			for(StackItemType i = 0; i < SIZE; i++){
				st->push(i + 100);
				tester_v->push_back(i + 100);
			}
		}

	void generalFeedback(bool success){
		if (success != true) 
			cout << "There are " << err << " errors in your code. You can find specific feedback in errorLog file if you chose to output to a file." << endl;
		else
			cout << "Successful code." << endl;
	}
};

int main(void){
	bool useFile = true;
	AStackTest test = AStackTest(useFile);

	test.run();
}