#include "AQueue.h"
#include "../ErrorRec.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <climits>

using namespace std;

/* Class used to automatically test the structure AQueue */
class AQueueTest {
	private:
		// Declare structures to be tested: AQueue object
		AQueue * qe = new AQueue(SIZE);
		AQueue * qe_default = new AQueue();

		// Declare testing variable: C++ vector
		vector<QueueItemType> tester_v; 

		// Auxiliary variables
		QueueItemType dummy = 100; // insert dummy value occasionally in testing 
	 	int err = 0; // counts errors found in the code

		// File relevant variables
		ErrorRec * record;

	public :

		// Instantiating custom queue
		static const int SIZE = 100;
		static const int MAX_SIZE = 1000;

		AQueueTest(bool useFile){
			record = new ErrorRec(useFile, "AQueue");
		}

		/* Used to run test cases */
		void run(){
			/* State 1: empty queue after init */

			// length(): returns number of elements in AQueue.
			int len = qe->length();
			if (len != 0) {
				record->printError("length() returns value other than 0 after init. Value returned:"+ to_string(len));
			}

			// isEmpty(): returns 1 if AQueue is empty, 0 otherwise
			bool isempty = qe->isEmpty();
			if (isempty != true) {
				record->printError("isEmpty() returns " + to_string(isempty) + " after init.");
			}

			// frontValue(): returns top of AQueue
			QueueItemType firstElement = qe->frontValue();
			if (firstElement != -1) {
				record->printError("frontValue() returns value other than -1 after init. Element returned: " + to_string(firstElement));
			}

			// toString(): returns AQueue content parsed in string format
			string tostring = qe->toString();
			if (tostring != "") {
				record->printError("toString() returns value other than '' after init. Value returned: " + tostring);
			}

			// clear(): empties AQueue. No returned value.
			qe->clear();
			len = qe->length();
			if (len != 0) {
				record->printError("length() returned value other than 0 after running clear (init testing). Value returned: " + to_string(len));
			}
			// dequeue(): removes and returns top value of AQueue.
			QueueItemType dequeued = qe->dequeue();
			if (dequeued != -1) {
				record->printError("dequeue() returned value other than -1 after init. Value returned: " + to_string(dequeued));
			}
			// enqueue(): adds a QueueItemType to the top of AQueue. 
			bool enqueue_return = qe->enqueue(dummy);
			if (enqueue_return != true) {
				record->printError("enqueue() returned value other than 'true' after init. Enqueuing dummy value:" + to_string(dummy) +". Value returned: " + to_string(enqueue_return));
			}

			// frontValue(): see above
			firstElement = qe->frontValue();
			if (firstElement != dummy){
				record->printError("Unexpected firstElement in queue (init test, enqueuing dummy). firstElement: " + to_string(firstElement) + ". Expected dummy value: " + to_string(dummy));
			}

			// clear dummy value
			qe->clear();

			/* State 2: normally-filled queue */
			fillQueue(qe, &tester_v, SIZE);

			// cmp length to size of tester_v
			int testersize = tester_v.size();
			len = qe->length();
			if (len != testersize) {
				record->printError("length() returns value different than size of tester_v. Length of queue: " + to_string(len) + " Size of tester_v: " + to_string(testersize) + "\n\n");
			}

			// cmp length to expected size of tester_v
			len = qe->length();
			if (len != SIZE) {
				record->printError("length() returns value different than SIZE. Length of queue: " + to_string(len) + " SIZE: " + to_string(SIZE));
			}

			// check isEmpty
			isempty = qe->isEmpty();
			if (isempty != false) {
				record->printError("isEmpty() returns " + to_string(isempty) + " in normally-filled queue. Expected value: false.");
			}

			// check firstElement
			QueueItemType frontvalue_t = tester_v.front();
			firstElement = qe->frontValue();
			if (firstElement != frontvalue_t) {
				record->printError("Unexpected frontValue() in normally-filled queue. firstElement: " + to_string(firstElement) + ". Expected front value: " + to_string(frontvalue_t));
			}

			// check toString
			string stringtester = toString(tester_v);
			tostring = qe->toString();
			if ( tostring != stringtester) {
				record->printError("Unexpeted toString() value. toString returned: " + tostring + ". Tester_v: "+ stringtester);
			}

			// check(): removes and checks all values of queue
			check(qe, tester_v, SIZE);

			// check if tester_v and queue still have same size  
			testersize = tester_v.size();
			len = qe->length();
			if (testersize != len){
				record->printError("Queue and tester_v do not have the same length after check. Size of tester: " + to_string(testersize) + ". Size of queue: " + to_string(len));
			}

			// make sure tester_v is empty
			tester_v.clear();

			/* State 3: overly-filled queue */
			fillQueue(qe, &tester_v, SIZE);

			// enqueue in a full queue
			enqueue_return = qe->enqueue(dummy);
			if (enqueue_return != 0){
				record->printError("Enqueued in an overly-filled queue.");
			}

			/* State 4: Special cases */
			qe->clear();
			tester_v.clear();

			/* Testing default constructor */
			fillQueue(qe_default, &tester_v, MAX_SIZE);

			// check length
			len = qe_default->length();
			if (len != MAX_SIZE) {
				record->printError("Unexpected length of st_default. Length of qe_default: " + to_string(len) + ". Expected length: " + to_string(MAX_SIZE));
			}

			stringtester = toString(tester_v);
			tostring = qe_default->toString();
			if ( tostring != stringtester) {
				record->printError("Unexpeted toString() value. toString returned: " + tostring + ". Tester_v: "+ stringtester);
			}

			// remove and check all values of Queue
			check(qe_default, tester_v, MAX_SIZE);

			// generalFeedback(): says if code is successful or not.
			record->feedback();
		}
		
		// check(): removes and checks all values of queue
		void check(AQueue* qe, vector<QueueItemType> tester_v, int SIZE){
			int qe_dequeued;
			int tv_dequeued;
			vector<QueueItemType> temp;
			
			for (int i = SIZE; i > 0; i--){
				qe_dequeued = qe->dequeue();
				tv_dequeued = tester_v.front();
				if (qe_dequeued != tv_dequeued) {
					record->printError("In check: queue dequeue different than tester_v front. Queue dequeued: " + to_string(qe_dequeued) + ". Tester_v front: " + to_string(tv_dequeued));
				}
				tester_v.erase(tester_v.begin());
				temp.push_back(qe_dequeued);
			}

			//Restore values
			for (int i = SIZE; i > 0; i--){
				qe->enqueue(temp.front());
				temp.erase(temp.begin());
			}
		}

		//converts the test queue to string following the expected string format of AQueue
		string toString(vector<QueueItemType> tester_v) {
			string str = "";
		    for (int i = 0; i < tester_v.size(); i++) str = str + to_string(tester_v[i]) + " ";
		
		    return str;
		}

		// initialize the test queue
		void fillQueue(AQueue* qe, vector<QueueItemType>* tester_v, int SIZE){
			for(QueueItemType i = 0; i < SIZE; i++){
				qe->enqueue(i + 100);
				tester_v->push_back(i + 100);
			}
		}
};

int main(void){
	bool useFile = true;
	AQueueTest test = AQueueTest(useFile);

	test.run();
	
	return 0;
}
