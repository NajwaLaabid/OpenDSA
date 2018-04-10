/* Queue ADT - general implementation
 * April 2018
 */
#ifndef Queue_H
#define Queue_H
#include <string>

using namespace std;

const int MAX_SIZE = 1000;
typedef int QueueItemType;

/* *** OpenDSATag: QueueADT *** */
class Queue { // Queue class ADT
public: 
  // Empties the queue
  virtual void clear() =0; 

  // Checks if queue isEmpty
  virtual bool isEmpty() =0;

  // Transforms queue to string
  virtual string toString() =0;

  // Appends a new item at the end of the queue ("enqueues" item)
  // Returns a boolean (1 = successful, 0 = error)
  virtual bool enqueue(const QueueItemType& newItem) =0;  

  // Removes and returns first element in queue
  virtual QueueItemType dequeue() =0; 

  // Returns a copy of the first element in queue
  virtual QueueItemType frontValue() =0; 

  // Returns length of queue
  virtual int length() =0; 

  //Destructor: required for polymorphism
  virtual ~ Queue () = default;
  /* *** OpenDSAEndTag: QueueADT *** */
};

#endif /* AQueue H */
