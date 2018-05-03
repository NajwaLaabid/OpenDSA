typedef int LinkItemType;

/* *** ODSATag: Freelink *** */
class FLink {         // Singly linked list node with freelist support
  LinkItemType e;  // Value for this node
  FLink* n;    // Point to next node in list

public:
  // Constructors
  FLink(LinkItemType it, FLink* inn) { e = it; n = inn; }
  FLink(FLink* inn) { e = (LinkItemType)NULL; n = inn; }

  LinkItemType element() { return e; }           // Return the value
  LinkItemType setElement(LinkItemType it) { e = it; return e; } // Set element value
  FLink* next() { return n; }                // Return next link
  FLink* setNext(FLink* inn) { n = inn; return n; }      // Set next link

  // Extensions to support freelists
  static FLink* freelist;     // Freelist for the class

  // Return a new link, from freelist if possible
  static FLink* get(LinkItemType it, FLink* inn) {
    if (freelist == NULL)
      return new FLink(it, inn);        // Get from "new"
    FLink* temp;
    if (freelist) {
      FLink* temp = freelist;              // Get from freelist
      freelist = freelist->next();
      temp->setElement(it);
      temp->setNext(inn);
    }

    return temp;
  }

  // Return a link node to the freelist
  void release() {
    e = (LinkItemType)NULL;   // Drop reference to the element
    n = freelist;
    freelist = this;
  }
};
/* *** ODSAendTag: Freelink *** */