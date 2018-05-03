/* *** ODSATag: AList *** */
// Array-based list implementation
/* *** ODSATag: AListVars *** */
class AList : public List {
  LinkItemType* listArray; // Array holding list elements
  const int DEFAULT_SIZE = 10; // Default size
  int maxSize;                    // Maximum size of list
  int listSize;                   // Current # of list items
  int curr;                       // Position of current element
/* *** ODSAendTag: AListVars *** */

public:
/* *** ODSATag: Constructors *** */
  // Constructors
  // Create a new list object with maximum size "size"
  AList(int size) {
    maxSize = size;
    listSize = curr = 0;
    listArray = new LinkItemType[size];         // Create listArray
  }
  // Create a list with the default capacity
  AList() { AList(DEFAULT_SIZE); }          // Just call the other constructor
/* *** ODSAendTag: Constructors *** */

  void clear() { listSize = curr = 0; }  // Simply reinitialize values

/* *** ODSATag: AListInsert *** */
  // Insert "it" at current position
  bool insert(LinkItemType it) {
    if (listSize >= maxSize) return false;
    for (int i=listSize; i>curr; i--)  // Shift elements up
      listArray[i] = listArray[i-1];   //   to make room
    listArray[curr] = it;
    listSize++;                        // Increment list size
    return true;
  }
/* *** ODSAendTag: AListInsert *** */

/* *** ODSATag: AListAppend *** */
  // Append "it" to list
  bool append(LinkItemType it) {
    if (listSize >= maxSize) return false;
    listArray[listSize++] = it;
    return true;
  }
/* *** ODSAendTag: AListAppend *** */

/* *** ODSATag: AListRemove *** */
  // Remove and return the current element
  LinkItemType remove() {
    if ((curr<0) || (curr>=listSize))  // No current element
      return (LinkItemType)NULL;
    LinkItemType it = listArray[curr];       // Copy the element
    for(int i=curr; i<listSize-1; i++) // Shift them down
      listArray[i] = listArray[i+1];
    listSize--;                        // Decrement size
    return it;
  }
/* *** ODSAendTag: AListRemove *** */

  void moveToStart() { curr = 0; }       // Set to front
  void moveToEnd() { curr = listSize; }  // Set at end
  void prev() { if (curr != 0) curr--; } // Move left
  void next() { if (curr < listSize) curr++; } // Move right
  int length() { return listSize; }      // Return list size
  int currPos() { return curr; }         // Return current position

  // Set current list position to "pos"
  bool moveToPos(int pos) {
    if ((pos < 0) || (pos > listSize)) return false;
    curr = pos;
    return true;
  }

  // Return true if current position is at end of the list
  bool isAtEnd() { return curr == listSize; }

  // Return the current element
  LinkItemType getValue() {
    if ((curr < 0) || (curr >= listSize)) // No current element
      return (LinkItemType)NULL;
    return listArray[curr];
  }
  
  // Check if the list is empty
  bool isEmpty() { return listSize == 0; }
  
  string toString() {
		string out;

		out.append("< ");
		for (int i = 0; i < curr; i++) {
			out.append( to_string(listArray[i]) );
			out.append(" ");
		}
		out.append("| ");
		for (int i = curr; i < listSize; i++) {
			out.append( to_string(listArray[i]) );
			out.append(" ");
		}
		out.append(">");
		return out;
	}
};
/* *** ODSAendTag: AList *** */