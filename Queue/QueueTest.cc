#include "AQueue.h"
#include "LQueue.h"
#include "../ErrorRec.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>
#include <typeinfo>

using namespace std;

/* Class used to automatically test the structure Queue.
 * Current testing strategy:
 	* Three main functions: 
 		* One for initialization : run()
 		* One for functions to be tested on an empty queue: checkEmpty()
 		* One for all functions implemented in the ADT: check()
 	* Functions in play (testing schema):
 		* Run() initializes custom ADT and built-in ADT
 		* Call checkEmpty() on empty ADT
 		* Insert elements in ADT and call check() on every insert
*/

class QueueTest {
	public :

		// The number of items stored in queue during the test
		const int TEST_SIZE = 100;
		// True if you want to create a text file to record errors
		bool useFile = true;
		// Instance of ErrorRec class which holds the number of errors and prints
		// out error messages
		ErrorRec* record;
		// built-in structure
		vector<QueueItemType> tester_v;
		// auxiliary vector, used in function check()
		vector<QueueItemType> temp;
		// custom ADT
		Queue* q;

		QueueTest(bool value){
			useFile = value;
		}

		void run( Queue* queue, string className ) {
			// empty vectors from potential previous runs
			temp.clear();
			tester_v.clear();

			// initialize a new file for every run of the function
			// (probably testing a new class)
			record = new ErrorRec( useFile, className );

			// initialize custom queue
			q = queue;

			// first round of tests: on an empty queue
			checkEmpty();

			// second round of tests: run all functions on every addition
			// for(int i = 0; i < TEST_SIZE; i++) 
			// 	check(100 + i);

			// output general feedback: success/ error message
			record->feedback();
		}

		void checkEmpty() {
			// length(): returns number of elements in queue.
			if ( q->length() != 0 ) 
				record->printError( "length() returns value other than 0 after init. Value returned:"+ to_string( q->length() ) );
			
			// isEmpty(): returns 1 if queue is empty, 0 otherwise
			if ( q->isEmpty() != true ) 
				record->printError( "isEmpty() returns " + to_string( q->isEmpty() ) + " after init." );

			// frontValue(): returns top of queue
			if ( q->frontValue() != -1 ) 
				record->printError( "frontValue() returns value other than -1 after init. Value returned: " + to_string( q->frontValue() ) );

			// dequeue(): removes and returns front value of queue.
			QueueItemType dequeued = q->dequeue();
			if ( dequeued != -1 ) 
				record->printError( "dequeue() returned value other than -1 after init. Value returned: " + to_string( dequeued ) );

			// toString(): returns queue content parsed in string format
			if ( q->toString() != "" )
				record->printError( "toString() returns value other than '' after init. Value returned: " + q->toString() );

			// // clear(): empties queue. No returned value.
			// q->clear();
		
			// // check length after clear
			// if ( q->length() != 0 ) 
			// 	record->printError( "length() returned value other than 0 after running clear (testing empty queue). Value returned: " + to_string( q->length() ) );		
		
		}

		void check( QueueItemType item ){
			
			// Add the item to both queues
			q->enqueue(item);
			tester_v.push_back(item);

			//cmp length to size of tester_v
			if (q->length() != tester_v.size()) 
				record->printError("length() of queue: " + to_string(q->length())
					+ ". Length expected: " + to_string(tester_v.size()));
			
			// check isEmpty
			if (q->isEmpty() != false)
				record->printError("isEmpty() returns " + to_string(q->isEmpty()) + " in normally-filled queue. Expected value: false.");

			// check frontValue
			if ( q->frontValue() != tester_v.front() ) 
				record->printError("Unexpected frontValue() in normally-filled queue. frontValue: " + to_string(q->frontValue()) + ". Expected top value: " + to_string(tester_v.front()));

			// check toString
			if ( q->toString() != toString(tester_v) ) 
				record->printError( "Unexpeted toString() value. toString returned: " + q->toString() + ". Tester_v: "+ toString(tester_v) );
			
			/* Memory problem */
			
			/*
				QueueItemType q_dequeued;
				QueueItemType tv_dequeued;
				
				int curSize = st->length();
				
				// cout << st->length() << endl;
				for(int i = 0; i < curSize; i++) {
					q_dequeued = st->dequeue();
					tv_dequeued = tester_v.front();
					if (q_dequeued != tv_dequeued) 
						record->printError( "Class: " + className + ". In check: queue dequeue different than tester_v dequeue. Queue dequeue: " + to_string(q_dequeued) + ". Tester_v dequeue: " + to_string(tv_dequeued) );
					
					st->enqueue(q_dequeued);
					tester_v.push_back( q_dequeued );
				}
			*/
		}

		//converts the test queue to string following the expected string format of AQueue
		string toString(vector<QueueItemType> tester_v) {
			string str = "";
		    for (int i = 0; i < tester_v.size(); i++) str = str + to_string(tester_v[i]) + " ";
		
		    return str;
		}
};

int main(void){
	// true when want to use log files
	// false when prefer to print to screen
	bool useFile = true; 
	// instatiating testing class
	QueueTest test = QueueTest(useFile);

	int size = 100;

	// Testing array implementation of queue
	AQueue * aQ = new AQueue(size);
	AQueue * aQ_default = new AQueue();

	// test.run(aQ, "AQueue");
	// test.run(aQ_default, "aQueue_default");

	// Testing linked list implementation of queue
	LQueue* lQ = new LQueue();

	test.run(lQ, "LQueue");
	
	return 0;
}
