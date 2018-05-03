/* List ADT - general implementation
 * April 2018
 */

/* *** ODSATag: ListADT *** */
/* *** ODSATag: ListADT1 *** */

// List class ADT.

typedef int LinkItemType;

class List {
public:
	// Remove all contents from the list, so it is once again empty
	void clear();

	// Insert "it" at the current location
  	// The client must ensure that the list's capacity is not exceeded
   	bool insert(LinkItemType it);

   	// Append "it" at the end of the list
  	// The client must ensure that the list's capacity is not exceeded
  	bool append(LinkItemType it);

  	// Remove and return the current element
  	LinkItemType remove();
	
	/* *** ODSAendTag: ListADT1 *** */
  	// Set the current position to the start of the list
   	void moveToStart();

  	// Set the current position to the end of the list
   	void moveToEnd();

   	// Move the current position one step left, no change if already at beginning
   	void prev();

  	// Move the current position one step right, no change if already at end
   	void next();

   	// Return the number of elements in the list
   	int length();
	/* *** ODSAendTag: ListADT2 *** */

   	/* *** ODSATag: ListADT3 *** */
  	// Return the position of the current element
   	int currPos();

  	// Set the current position to "pos"
  	bool moveToPos(int pos);

  	// Return true if current position is at end of the list
   	bool isAtEnd();

  	// Return the current element
   	LinkItemType getValue();
  
  	bool isEmpty();

  	//Destructor: required for polymorphism
  	virtual ~ List () = default;
};
/* *** ODSAendTag: ListADT3 *** */
/* *** ODSAendTag: ListADT *** */

