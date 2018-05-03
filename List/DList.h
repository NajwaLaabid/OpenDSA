#include "List.h"
#include "DLink.h"
#include <iostream>
#include <string>

using namespace std;

class DList: public List {
  DLink* head;         // Pointer to list header
  DLink* tail;         // Pointer to last element
  DLink* curr;         // Access to current element
  int listSize;      // Size of list

public:
  // Constructors
  DList() { }
  DList(int size) { this; }     // Constructor -- Ignore size

  // Remove all elements
  void clear() {
    curr = tail = new DLink(NULL, NULL); // Create trailer
    head = new DLink(NULL, NULL);        // Create header
    tail->setPrev(head);                 // Set prev link for trailer
    listSize = 0;
  }

/* *** ODSATag: Dlist *** */
  // Insert "it" at current position
/* *** ODSATag: DListInsert *** */
  bool insert(LinkItemType it) {
    curr = new DLink(it, curr->prev(), curr);
    curr->prev()->setNext(curr);
    curr->next()->setPrev(curr);
    listSize++;
    return true;
  }
/* *** ODSAendTag: DListInsert *** */

// Append "it" to list
/* *** ODSATag: DListAppend *** */
  bool append(LinkItemType it) {
    tail->setPrev(new DLink(it, tail->prev(), tail));
    tail->prev()->prev()->setNext(tail->prev());
    if (curr == tail) curr = tail->prev();
    listSize++;
    return true;
  }
/* *** ODSAendTag: DListAppend *** */

  // Remove and return current element
/* *** ODSATag: DListRemove *** */
  LinkItemType remove() {
    if (curr == tail) return (LinkItemType)NULL;        // Nothing to remove
    LinkItemType it = curr->element();           // Remember value
    curr->prev()->setNext(curr->next());     // Remove from list
    curr->next()->setPrev(curr->prev());
    curr = curr->next();
    listSize--;                           // Decrement node count
    return it;                            // Return value removed
  }
/* *** ODSAendTag: DListRemove *** */

// Move curr one step left; no change if at front
/* *** ODSATag: DListPrev *** */
  void prev() {
    if (curr->prev() != head)   // Can't back up from list head
      curr = curr->prev();
  }
/* *** ODSAendTag: DListPrev *** */

/* *** ODSAendTag: Dlist *** */

  void moveToStart() { curr = head->next(); } // Set curr at list start
  void moveToEnd() { curr = tail; }     // Set curr at list end
  // Move curr one step right; no change if now at end
  void next() { if (curr != tail) curr = curr->next(); }
  int length() { return listSize; } // Return list length
  // Return the position of the current element
  int currPos() {
    DLink* temp = head->next();
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
  
  // Check if the list is empty
  bool isEmpty() { return listSize == 0; }
  
  string toString() {
		DLink* temp = head->next();
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

  // Test for XOR concept
  void XOR() {
    int a = 1, b = 1, c = 1;
    /* *** ODSATag: XOR *** */
    a = a + b;
    b = a - b; // Now b contains original value of a
    a = a - b; // Now a contains original value of b
    /* *** ODSAendTag: XOR *** */
  }

};