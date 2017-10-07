#include "AStack.h"
#include <iostream>

using namespace std;

int main (void){

	StackItemType it;
	const int size = 5;
	int res=0;
	AStack * st = new AStack(size);

	for(it = 1; it < 10; it++){
		res = st->push(it);
		if(res == 1) cout << "Just pushed: " << st->topValue() << ". New top: " << st->length() << endl; 
		else cout << "Full Stack, could not push element: "<< it << endl;
	}

	//test toString
	cout << "Stack in string form: " << st->toString() << endl;

	int old_length = st->length();
	int half = st->length() / 2;

	//pop half the stack
	for(int i = 0; i < half; i++)
		cout << "Just popped: " << st->pop() << endl;

	//get new length of the stack
	cout << "Expected length:"<< old_length - half << "." << " Actual length: " << st->length() << endl;

	//get the values of the rest of stack (without popping)
	cout << "New top value: " << st->topValue() <<endl;

	st->clear();
	//round 2
	int a = 20, b = 25, c = 23;
	st->push(a);
	st->push(b);
	st->push(c);

	cout << "Elm popped: expected: 23, actual:  " << st->pop() << endl;
	cout << "Elm popped: expected: 25, actual:  " << st->pop() << endl;
	cout << "New length: " << st->length() << endl;

	st->clear();

	cout  << "Length after clear: " << st->length() << endl;

	return 0;
}