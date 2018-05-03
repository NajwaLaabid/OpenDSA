#include "FLink.h"

// Linked list implementation that uses a Freelist
class FList: public List {
  FLink* head;         // Pointer to list header
  FLink* tail;         // Pointer to last element
  FLink* curr;         // Access to current element
  int listSize;      // Size of list

public:
  // Constructors
  FList() { }

  // Remove all elements
  void clear() {
    while (head != NULL) {
      FLink* temp = head->next();
      head->release();
      head = temp;
    }
    curr = tail = FLink::get((LinkItemType)NULL, NULL); // Create trailer
    head = FLink::get((LinkItemType)NULL, tail);        // Create header
    listSize = 0;
  }
  
/* *** ODSATag: Freelist *** */
  // Insert "it" at current position
  bool insert(LinkItemType it) {
    curr->setNext(FLink::get(curr->element(), curr->next())); // Get link
    curr->setElement(it);
    if (tail == curr) tail = curr->next();    // New tail
    listSize++;
    return true;
  }

  // Append "it" to list
  bool append(LinkItemType it) {
    tail->setNext( FLink::get( (LinkItemType)NULL, NULL ) );
    tail->setElement(it);
    tail = tail->next();
    listSize++;
    return true;
  }

  // Remove and return current element
  LinkItemType remove () {
    if (curr == tail) return (LinkItemType)NULL;          // Nothing to remove
    LinkItemType it = curr->element();             // Remember value
    curr->setElement(curr->next()->element()); // Pull forward the next element
    if ( curr->next() == tail ) tail = curr;   // Removed last, move tail
    FLink* tempptr = curr->next();             // Remember the link
    curr->setNext(curr->next()->next());       // Point around unneeded link
    tempptr->release();                      // Release the link
    listSize--;                             // Decrement element count
    return it;                              // Return value
  }
  /* *** ODSAendTag: Freelist *** */

  void moveToStart() { curr = head->next(); } // Set curr at list start
  void moveToEnd() { curr = tail; }          // Set curr at list end

  // Move curr one step left; no change if now at front
  void prev() {
    if (head->next() == curr) return;         // No previous element
    FLink* temp = head;
    // March down list until we find the previous element
    while (temp->next() != curr) temp = temp->next();
    curr = temp;
  }

  // Move curr one step right; no change if now at end
  void next() { if (curr != tail) curr = curr->next(); }

  int length() { return listSize; }          // Return list length


  // Return the position of the current element
  int currPos() {
    FLink* temp = head->next();
    int i;
    for (i=0; curr != temp; i++)
      temp = temp->next();
    return i;
  }
  
  // Move down list to "pos" position
  bool moveToPos(int pos) {
    if ((pos < 0) || (pos > listSize)) return false;
    curr = head->next();
    for(int i=0; i<pos; i++) curr = curr->next();
    return true;
  }

  // Return true if current position is at end of the list
  bool isAtEnd() { return curr == tail; }

  // Return current element value
  LinkItemType getValue() {
    if(curr == tail) return (LinkItemType)NULL;
    return curr->element();
  }

  bool isEmpty() {
    return listSize == 0;
  }
  
  string toString() {
		FLink* temp = head->next();
		string out;

		out.append("< ");
		for (int i = 0; i < currPos(); i++) {
			out.append( to_string( temp->element() ) );
			out.append(" ");
			temp = temp->next();
		}
		out.append("| ");
		for (int i = currPos(); i < listSize; i++) {
			out.append( to_string( temp->element() ) );
			out.append(" ");
			temp = temp->next();
		}
		out.append(">");
		return out;
	  }
};