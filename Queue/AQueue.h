#include "Queue.h"
#include <iostream>
#include <string>

using namespace std;

/* *** ODSATag: AQueue *** */ 
// Array-based queue implementation
/* *** ODSATag: AQueueVars *** */
class AQueue : public Queue{
  	QueueItemType queueArray[MAX_SIZE]; // Array holding queue items
  	const int QUEUE_SIZE; // Current number of queue items
  	int rear; // Position of last element of queue
    /* *** ODSAendTag: AQueueVars *** */

  public: 

  	// Constructor
    // Create a new queue element of size "size" 
  	AQueue(int size) : QUEUE_SIZE(size), rear(0) {
  		// Initialize the array
      rear = 0;
      for (int i = 0; i < QUEUE_SIZE; i++) queueArray[i] = 0;
  	} // End constructor

    // Default constructor
    // Create queue in MAX_SIZE
    AQueue() : QUEUE_SIZE(MAX_SIZE) {
      // Initialize the array
      rear = 0;
      for (int i = 0; i < QUEUE_SIZE; i++) queueArray[i] = 0;
    }// End default constructor

    // Checks if queue is empty
    bool isEmpty() { 
      return !rear; 
    } 

    // Reinitializes queue
  	void clear() { 
      rear = 0;   // Simply reinitialize rear
    }

    // Returns the queue in a string form
    string toString() {
      string str = "";
      for (int i = 0; i < rear; i++) str = str + to_string(queueArray[i]) + " ";
      return str;
    }
  
    /* *** ODSATag: AQueueEnqueue *** */
    // Adds newItem to queue
  	bool enqueue(const QueueItemType& newItem) {
      if (rear == QUEUE_SIZE) return false; // Queue full, cannot enqueue
  		else {
  			queueArray[rear++] = newItem;
  			return true; // Enqueue successful
  		}
  	}
    /* *** ODSAendTag: AQueueEnqueue *** */

    /* *** ODSATag: AQueueDequeue *** */
    //Returns first element in queue and deletes it afterwards
  	QueueItemType dequeue() { 
      if (!isEmpty()) {
        // Store value of first element in queue
        QueueItemType first = queueArray[0];

        // Move all elements to the front of the queue by one position
        for(int i = 0; i < QUEUE_SIZE - 1; i++)
          queueArray[i] = queueArray[i+1];
        
        // Decrement rear
        rear--;

        // Return first element
        return first;
      } 

      else return (QueueItemType) -1;
    } 
    /* *** ODSAendTag: AQueueDequeue *** */

    //Returns first element (without deleting it)
  	QueueItemType frontValue() { 
      if (!isEmpty()) return queueArray[0];
      else return (QueueItemType) -1;
    } 

    //Returns current length of queue
  	int length() { return rear; } 

    //Destructor: required for polymorphism
    ~ AQueue () = default;
    /* *** OpenDSAendTag: AQueue *** */

};
