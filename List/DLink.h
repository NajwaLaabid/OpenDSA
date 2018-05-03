typedef int LinkItemType;
/* *** ODSATag: DLink *** */
class DLink {            // Doubly linked list node
  LinkItemType e;     // Value for this node
  DLink* n;       // Pointer to next node in list
  DLink* p;       // Pointer to previous node

public:
  // Constructors
  DLink() {}
  DLink(LinkItemType it, DLink* inp, DLink* inn) { e = it;  p = inp; n = inn; }
  DLink(DLink* inp, DLink* inn) { p = inp; n = inn; }

  // Get and set methods for the data members
  LinkItemType element() { return e; }                     // Return the value
  LinkItemType setElement(LinkItemType it) { e = it; return e; }    // Set element value
  DLink* next() { return n; }                          // Return next link
  DLink* setNext(DLink* nextval) { n = nextval; return n; } // Set next link
  DLink* prev() { return p; }                          // Return prev link
  DLink* setPrev(DLink* prevval) { p = prevval; return p; } // Set prev link

  DLink operator=(const DLink &arg) {
    if(this != &arg) { // check for self-assignment
      this->e = arg.e;
      this->n = arg.n;
      this->p = arg.p;
    }

    return *this;
  } // overloading the assignment operator

  bool operator==(const DLink &arg) {
    if(this->e == arg.e && this->n == arg.n && this->p == arg.p)
      return true;

    return false;
  }

  bool operator!=(const DLink &arg) {
    return !(*this == arg);
  }  
};
/* *** ODSAendTag: DLink *** */