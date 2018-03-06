#include "AStack.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

class AStackTest {
	private:
		AStack * st = new AStack(SIZE);
		AStack * st_default = new AStack();

		// instantiating testing structures 
		vector<StackItemType> tester_v; //testing using arrays

		// auxiliary variables
		StackItemType dummy = 100; // should be less than SIZE
	 	int err = 0;

		// file relevant code
		const string fileName = "errorLog.txt";
		ofstream errorLog;

	public :

		// instantiating custom stack
		static const int SIZE = 100;
		static const int MAX_SIZE = 1000;

		AStackTest(bool useFile){
			if (useFile == true) {
				errorLog.open(fileName);
			}
		}

		void run(){
			/* State 1: empty stack after init */
			// function: length
			int len = st->length();
			if (len != 0) {
				error("length() returns value other than 0 after init. Value returned:"+ to_string(len));
			}
			// function: isEmpty
			bool isempty = st->isEmpty();
			if (isempty != true) {
				error("isEmpty() returns " + to_string(isempty) + " after init.");
			}
			// function: topValue
			StackItemType topvalue = st->topValue();
			if (topvalue != -1) {
				error("topValue() returns value other than -1 after init. Value returned: " + to_string(topvalue));
			}
			// function: toString
			string tostring = st->toString();
			if (tostring != "") {
				error("toString() returns value other than '' after init. Value returned: " + tostring);
			}
			// function: clear()
			st->clear();
			len = st->length();
			if (len != 0) {
				error("length() returned value other than 0 after running clear (init testing). Value returned: " + to_string(len));
			}
			// function: pop()
			StackItemType popped = st->pop();
			if (popped != -1) {
				error("pop() returned value other than -1 after init. Value returned: " + to_string(popped));
			}
			// function: push()
			bool push_return = st->push(dummy);
			if (push_return != true) {
				error("push() returned value other than 'true' after init. Pushing dummy value:" + to_string(dummy) +". Value returned: " + to_string(push_return));
			}
			topvalue = st->topValue();
			if (topvalue != dummy){
				error("Unexpected topValue in stack (init test, pushing dummy). topValue: " + to_string(topvalue) + ". Expected dummy value: " + to_string(dummy));
			}
			// clear dummy value
			st->clear();

			/* State 2: normally-filled stack */
			fillStack(st, &tester_v, SIZE); // push tested inside this function

			// function: length (cmp to size of tester_v)
			int testersize = tester_v.size();
			len = st->length();
			if (len != testersize) {
				error("length() returns value different than size of tester_v. Length of stack: " + to_string(len) + " Size of tester_v: " + to_string(testersize) + "\n\n");
			}
			// function: length (cmp to expected size of tester_v)
			len = st->length();
			if (len != SIZE) {
				error("length() returns value different than SIZE. Length of stack: " + to_string(len) + " SIZE: " + to_string(SIZE));
			}
			// function: isEmpty
			isempty = st->isEmpty();
			if (isempty != false) {
				error("isEmpty() returns " + to_string(isempty) + " in normally-filled stack. Expected value: false.");
			}
			// function: topValue
			StackItemType backvalue = tester_v.back();
			topvalue = st->topValue();
			if (topvalue != backvalue) {
				error("Unexpected topValue() in normally-filled stack. topValue: " + to_string(topvalue) + ". Expected top value: " + to_string(backvalue));
			}
			// function: toString
			string stringtester = toString(tester_v);
			tostring = st->toString();
			if ( tostring != stringtester) {
				error("Unexpeted toString() value. toString returned: " + tostring + ". Tester_v: "+ stringtester);
			}
			// function: pop. check all values of stack
			check(st, tester_v, SIZE);
			// check if both tester_v and stack have same size still 
			testersize = tester_v.size();
			len = st->length();
			if (testersize != len){
				error("Stack and tester_v do not have the same length after check. Size of tester: " + to_string(testersize) + ". Size of stack: " + to_string(len));
			}

			// make sure tester_v is empty
			tester_v.clear();

			/* State 3: overly-filled stack */
			fillStack(st, &tester_v, SIZE);

			// function : push.
			push_return = st->push(dummy);
			if (push_return != 0){
				error("Pushed in an overly-filled stack.");
			}

			/* State 4: Special cases */
			st->clear();
			// SHL: Since this is automated testing, can we find a way to test this each time.
			// Naj: Which part of the code are we talking about here?
			
			// push NULL
			/*if (st->push(NULL) == 1)
				error("Pushed NULL.\n\n");*/
			// push string
			/*if (st->push("Hi") == 1)
				error("Pushed string when data type int.\n\n");*/

			/* Testing default constructor */
			fillStack(st_default, &tester_v, MAX_SIZE);

			// function: length
			len = st_default->length();
			if (len != MAX_SIZE) {
				error("Unexpected length of st_default. Length of st_default: " + to_string(len) + ". Expected length: " + to_string(MAX_SIZE));
			}
			// global check
			check(st_default, tester_v, MAX_SIZE);

			generalFeedback(err);
		}
		
		void check(AStack* st, vector<StackItemType> tester_v, int SIZE){
			// SHL: Does this limit StackItemType of int since you store the pop into these variables?
			// Naj: StackItemType is set in the header file to int, I can change to any other data type and test. Do you want me to do so?
					//Should I find a way to make this change automatic since this is automated testing?
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

		string toString(vector<StackItemType> tester_v) {
			string str = "";
		    for (int i = tester_v.size()-1; i >= 0; i--) str = str + to_string(tester_v[i]) + " ";
		
		    return str;
		}

		void error(string text) {
			err++;
			if ( !errorLog.is_open() ) 
				cout << text << "\n\n";
			else
				errorLog << text << "\n\n";
		}

		void fillStack(AStack* st, vector<StackItemType>* tester_v, int SIZE){
			for(StackItemType i = 0; i < SIZE; i++){
				st->push(i + 100);
				tester_v->push_back(i + 100);
			}
		}

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
}
