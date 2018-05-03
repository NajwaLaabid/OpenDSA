#include "List.h"
#include "Link.h"
#include <iostream>
#include <string>

using namespace std;

/* *** ODSATag: LList *** */
// Linked list implementation
/* *** ODSATag: LListVars *** */
class LList : public List {
	Link head;         // Pointer to list header
	Link tail;         // Pointer to last element
	Link curr;         // Access to current element
	int listSize;      // Size of list
/* *** ODSAendTag: LListVars *** */

/* *** ODSATag: LListCons *** */
public:
	// Constructors
  	//LList(int size) { this(); }     // Constructor -- Ignore size
  	LList() {}	

  	// Remove all elements
  	void clear() {
	    curr = tail = new Link(NULL); // Create trailer
	    head = new Link(tail);        // Create header
	    listSize = 0;
  	}
/* *** ODSAendTag: LListCons *** */

/* *** ODSATag: LListInsert *** */
  	// Insert "it" at current position
  	bool insert(Link it) {
	    curr.setNext(new Link(curr.element(), curr.next()));
	    curr.setElement(it.element());
	    if ( ( tail.element() == curr.element() ) && ( tail.next() == curr.next() ) ) tail = curr.next();  // New tail
	    listSize++;
	    return true;
  	}
/* *** ODSAendTag: LListInsert *** */
  	
  	// Append "it" to list
  	bool append(Link it) {
	    tail.setNext(new Link(NULL));
	    tail.setElement(it.element());
	    tail = tail.next();
	    listSize++;
	    return true;
	}

/* *** ODSATag: LListRemove *** */
	// Remove and return current element
	Link remove () {
		if ( tail == curr ) return NULL;          // Nothing to remove
		Link it = curr;             // Remember value
		curr.setElement(curr.next()->element()); // Pull forward the next element
		if (curr.next() == tail.next()) tail = curr;   // Removed last, move tail
		curr.setNext(curr.next()->next());       // Point around unneeded link
		listSize--;                             // Decrement element count
		return it;                              // Return value
	}
/* *** ODSAendTag: LListRemove *** */

	void moveToStart() { curr = head.next(); } // Set curr at list start
	void moveToEnd() { curr = tail; }          // Set curr at list end

/* *** ODSATag: LListPrev *** */
	// Move curr one step left; no change if now at front
	void prev() {
		if ( head == curr ) return; // No previous element
		Link temp = head;
		// March down list until we find the previous element
		while ( *(temp.next()) != curr ) temp = *(temp.next());
		curr = temp;
	}
/* *** ODSAendTag: LListPrev *** */

/* *** ODSATag: LListNext *** */
	// Move curr one step right; no change if now at end
	void next() { if (curr != tail) curr = curr.next(); }

/* *** ODSAendTag: LListNext *** */

	int length() { return listSize; } // Return list length

	// Return the position of the current element
	int currPos() {
		Link temp = *(head.next());
		int i;
		for (i=0; curr != temp; i++)
		  temp = *(temp.next());
		return i;
	}

/* *** ODSATag: LListPos *** */
	// Move down list to "pos" position
	bool moveToPos(int pos) {
		if ((pos < 0) || (pos > listSize)) return false;
		curr = *(head.next());
		for(int i=0; i<pos; i++) curr = *(curr.next());
		return true;
	}
/* *** ODSAendTag: LListPos *** */

	// Return true if current position is at end of the list
	bool isAtEnd() { return curr == tail; }

	// Return current element value. Note that null gets returned if curr is at the tail
	LinkItemType getValue() { return curr.element(); }

	// Check if the list is empty
	bool isEmpty() { return listSize == 0; }
  
	string toString() {
		Link temp = *(head.next());
		string out;

		out.append("< ");
		for (int i = 0; i < currPos(); i++) {
			out.append( to_string( temp.element() ) ); // only used if object type is numeric
			out.append(" ");
			temp = *(temp.next());
		}

		out.append("| ");
		for (int i = currPos(); i < listSize; i++) {
			out.append( to_string( temp.element() ) );
			out.append(" ");
			temp = *(temp.next());
		}

		out.append(">");
		return out;
	}
};
/* *** ODSAendTag: LList *** */

