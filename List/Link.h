typedef int LinkItemType;

class Link { 	// Singly linked list node class
	LinkItemType e = 0; // Value for this node
	Link* n;  // Point to next node in list

  public:
    // constructors
    Link() {}
    Link(LinkItemType it, Link* inn) { e = it; n = inn; } 
    Link(Link* inn) { n = inn; } 

  	LinkItemType element() { return e; } // Return the value
  	LinkItemType setElement(LinkItemType it) { e = it; return e;} // Set element value
  	Link* next() { return n; }  // Return next link
  	Link* setNext(Link* inn) { return n = inn; } // Set next link

  	// overloading operators: used to allow the use of "normal" c++ operators 
  	// (such as =, ==, !=, +...) on user-defined classes (in our case the Link class)
  	// overloading follows a specific syntax as described below

  	// overloading functions should start with the keyword operator
  	// the argument passed to such functions is a constant
  	// because it is not meant to be changed, assignments are only interested 
  	// in changing left-side operands' values.
  	// the assignment operator returns a reference to the assigned object
  	// the following function definition checks for self-assignment to avoid 
  	// undesired behavior induced by the implementation of the assignment action
  	Link operator=(const Link &arg) {
  		if(this != &arg) { // check for self-assignment
  			this->e = arg.e;
  			this->n = arg.n;
  		}

  		return *this;
  	} // overloading the assignment operator

  	bool operator==(const Link &arg) {
  		if(this->e == arg.e && this->n == arg.n)
  			return true;

  		return false;
  	}

  	bool operator!=(const Link &arg) {
  		return !(*this == arg);
  	}  
};

/* *** ODSAendTag: Link *** */