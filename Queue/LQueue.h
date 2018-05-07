/* *** ODSATag: LQueue1 *** */
#include "../List/Link.h"
#include <iostream>
#include <string>

using namespace std;

// Linked queue implementation
class LQueue: public Queue {
  Link* front; // Pointer to front queue node
  Link* rear;  // Pointer to rear queue node
  int size;   // Number of elements in queue

public:
  // Constructors
  LQueue() {}
  // LQueue() { init(); }
  LQueue(int size) { init(); } // Ignore size

  // Initialize queue
  void init() {
    front = new Link((LinkItemType)10, NULL);
    size = 0;
  }
/* *** ODSAendTag: LQueue1 *** */

  // Reinitialize queue
  void clear() { init(); }

  string toString() {
    string out;
    if(front != NULL) {
      out = to_string(front->element());
      // cout << front->e << endl;
    } else {

      for (Link* temp = front; temp != NULL;  temp = temp->next()) {
        out.append( to_string( temp->element() ) );
        out.append(" ");
      }

    }
    
    return out;
  }
/* *** ODSATag: LQueue2 *** */

/* *** ODSATag: LQueueEnqueue *** */
  // Put element on rear
  bool enqueue(const QueueItemType& it) {
    rear->setNext(new Link(it, NULL));
    rear = rear->next();
    size++;
    return true;
  }

/* *** ODSAendTag: LQueueEnqueue *** */

/* *** ODSATag: LQueueDequeue *** */
  // Remove and return element from front
  QueueItemType dequeue() {
    if (size == 0) return -1;
    QueueItemType it = front->next()->element(); // Store the value
    front->setNext(front->next()->next()); // Advance front
    if (front->next() == NULL) rear = front; // Last element
    size--;
    return it; // Return element
  }
/* *** ODSAendTag: LQueueDequeue *** */

  // Return front element
  QueueItemType frontValue() {
    if (size == 0) return -1;
    return front->next()->element();
  }

  // Return queue size
  int length() { return size; }

  // Check if the queue is empty
  bool isEmpty() { return size == 0; }
};
/* *** ODSAendTag: LQueue2 *** */