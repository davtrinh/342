// Include the header file
//
//
//  STUFF GOES HERE
//
//
#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <fstream>
template <typename Type>
class List {
	friend ostream& operator<<(ostream& output, const List<Type>& thelist) {
		Node* current = thelist.head;
		while (current != NULL) {
			output << *current->data;
			current = current->next;
		}
		return output;
	}
private:
	struct Node {    // the node in a linked list
		Type* data;  // pointer to data, operations in template type used
		Node* next;  // next node that this points to in a list
	};
	Node* head;      // pointer to first node in a linked list
public:
	List();                                // default constructor
	List(const List<Type>&);               // copy constructor
	~List();                               // destructor
	void buildList(ifstream&);             // builds a list with given file

	// insert [below], inserts a template type of the variable to be
	// used, into a given list (ideally of the same templated type)
	bool insert(Type*);

	// remove [below], attempts to remove a given type item from the
	// list, returns a pointer to the item if it's in the list,
	// otherwise (if the element is not in the list) the pointer is NULL
	bool remove(Type, Type*&);

	// retrieve [below], goes through the same ideas as remove [above] but
	// doesn't delete the node if found in the list
	bool retrieve(Type, Type*&);

	// merge [below], a list is merged (allowing duplicates) with two
	// sorted parameter lists - no new memory -  the parameter lists
	// are emptied afterwards into the this object list
	void merge(List<Type>&, List<Type>&);

	// intersect [below], takes two sorted lists and returns to the 
	// this object list, allocating memory for items that are common
	// in each set, parameters don't change unless one list is the same
	void intersect(List<Type>&, List<Type>&);

	// returns true if the head is null
	bool isEmpty() const;

	// deletes a list of items (if any) in the list and sets the head to null
	void makeEmpty();

	// assigns the right side of the operator to the left side being
	// assigned, copying in [new] matching data from the right side
	List<Type>& operator=(const List<Type>&);

	// returns true if both sides of the operator have
	// the same items in the list
	bool operator==(const List<Type>&) const;

	// returns false if both sides of the operator 
	// do not have the same items in the list
	bool operator!=(const List<Type>&) const;
};

//----------------------------------------------------------------------------
// List()
// Description: Default Constructor
template <typename Type>
List<Type>::List() {
	head = NULL;
}

//----------------------------------------------------------------------------
// List(const List& other)
// Description: Copy Constructor
template <typename Type>
List<Type>::List(const List<Type>& other) {
	head = NULL;
	if (other.head != NULL) {
		head = new Node();
		Node* otherPtr = other.head;
		Type* dataPtr = new Type();
		*dataPtr = *otherPtr->data;
		head->data = dataPtr;
		Node* lastPtr = head;
		while (otherPtr->next != NULL) {
			otherPtr = otherPtr->next;
			Type* nestedDataPtr = new Type();
			*nestedDataPtr = *otherPtr->data;
			Node* newNodePtr = new Node();
			newNodePtr->data = nestedDataPtr;
			lastPtr->next = newNodePtr;
			lastPtr = lastPtr->next;
		}
		lastPtr->next = NULL;
	}
}

//----------------------------------------------------------------------------
// ~List()
// Description: Destructor
template <typename Type>
List<Type>::~List() {
	makeEmpty();
}

//----------------------------------------------------------------------------
// buildList(ifstream& inFile)
// Description: create a list from a data file
template <typename Type>
void List<Type>::buildList(ifstream& inFile) {
	if (!isEmpty())
		makeEmpty();
	Type* dataPtr;
	bool success;
	bool successfulRead;
	for (;;) {
		dataPtr = new Type();
		successfulRead = dataPtr->setData(inFile);
		if (inFile.eof()) {
			delete dataPtr;
			break;
		}
		if (successfulRead) {
			success = insert(dataPtr);
		}
		else {
			delete dataPtr;
			dataPtr = NULL;
		}
		if (!success)
			break;
	}
}

//----------------------------------------------------------------------------
// insert(Type* dataptr)
// Description: insert data fed from a data pointer into the list
template <typename Type>
bool List<Type>::insert(Type* dataptr) {
	if (dataptr == NULL)
		return false;
	Node* ptr = new Node();
	ptr->data = dataptr;
	if (isEmpty() || *ptr->data < *head->data) {
		ptr->next = head;
		head = ptr;
	}
	else {
		Node* previous = head;
		Node* current = head->next;
		while (current != NULL && *current->data < *ptr->data) {
			previous = current;
			current = current->next;
		}
		ptr->next = current;
		previous->next = ptr;
	}
	return true;
}

//----------------------------------------------------------------------------
// remove(const Type* dataPtr, Type*& retValPtr)
// Description: remove data element from the list and
//              return pointer via param's
template <typename Type>
bool List<Type>::remove(Type dataPtr, Type*& retValPtr) {
	retValPtr = NULL; // initialize the address of a pointer
	if (head == NULL) {
		return false;
	}
	if (*head->data == dataPtr) {
		retValPtr = head->data;
		return true;
	}
	Node* previous = head;
	Node* current = head->next;
	while (current != NULL) {
		if (*current->data == dataPtr) { // find the item to remove
			retValPtr = current->data;
			delete current->data;
			current->data = NULL;
			previous->next = current->next;
			delete current;
			current = NULL;
			return true;
		}
		previous = previous->next;
		current = current->next;
	}
	return false;
}

//----------------------------------------------------------------------------
// retrieve(const Type* dataPtr, Type*& retValPtr)
// Description: same as remove except no deleting
template <typename Type>
bool List<Type>::retrieve(Type dataPtr, Type*& retValPtr) {
	retValPtr = NULL; // initialize the address of a pointer
	if (head == NULL) {
		return false;
	}
	if (*head->data == dataPtr) {
		return true;
	}
	Node* current = head->next;
	while (current != NULL) {
		if (*current->data == dataPtr) { // if matching, then assign
			retValPtr = current->data;   // retValPtr the address to pointer
			return true;
		}
		current = current->next;
	}
	return false;
}

//----------------------------------------------------------------------------
// merge(List<Type>& a, List<Type>& b)
// Description: given any list condition, merge the params to the
//              calling list, without allocating any new memory.
template <typename Type>
void List<Type>::merge(List<Type>& ListA, List<Type>& ListB) {
	if (*this == ListA && *this == ListB)
		return;
	if (ListA.head == NULL && ListB.head == NULL) {
		makeEmpty();
		return;
	}
	if (this != &ListA && this != &ListB) {
		makeEmpty();
	}
	if (&ListA == &ListB) {
		cout << "IT EQUALSSSS" << endl;

	}
	Node* mergeInto;
	Node* takeOutOf;
	Node* holder;
	Node* temp = NULL;
	// [below] figure out which head is smaller
	// and start list to "mergeInto" with that head
	if (ListA.head != NULL && ListB.head != NULL) {
		if (&ListA == &ListB) {
			mergeInto = ListA.head;
			takeOutOf = NULL;
		}
		else
		if (*ListA.head->data < *ListB.head->data) {
			mergeInto = ListA.head;
			takeOutOf = ListB.head;
		}
		else {
			takeOutOf = ListA.head;
			mergeInto = ListB.head;
		}
	}
	else if (ListA.head == NULL && ListB.head != NULL) {
		cout << "BANZAIIII" << endl;
		mergeInto = ListB.head;
		takeOutOf = NULL;
	}
	else if (ListA.head != NULL && ListB.head == NULL) {
		mergeInto = ListA.head;
		takeOutOf = NULL;
	}
	holder = mergeInto; // save the beginning of the list for "this" head
	while (mergeInto->next != NULL) {
		if (takeOutOf == NULL)
			mergeInto = mergeInto->next;
		else if (*mergeInto->next->data == *takeOutOf->data) {
			mergeInto = mergeInto->next;
			temp = mergeInto->next;
			mergeInto->next = takeOutOf;
			mergeInto = mergeInto->next;
			takeOutOf = temp;
		}
		else if (*mergeInto->next->data < *takeOutOf->data) {
			mergeInto = mergeInto->next;
		}
		else {
			temp = mergeInto->next;
			mergeInto->next = takeOutOf;
			takeOutOf = temp;
		}
	}
	ListA.head = NULL;
	ListB.head = NULL;

	// This points the current list to the other list if the current
	// list has reached it's end. It also checks if list a and b are
	// the same in order to avoid an infinite loop.
	if (mergeInto->next == NULL && takeOutOf != NULL && (&ListA != &ListB)) {
		mergeInto->next = takeOutOf;
	}
	head = holder;
	mergeInto = NULL;
	takeOutOf = NULL;
}

//----------------------------------------------------------------------------
// intersect(List<Type>& a, List<Type>& b)
// Description: Given two parameter lists, find the items that are common
//              in boths lists and allocate the common items into the
//              this object list.
template <typename Type>
void List<Type>::intersect(List<Type>& ListA, List<Type>& ListB) {
	if (ListA.head == NULL || ListB.head == NULL) {
		makeEmpty();
		return;
	}
	if (*this == ListA && *this == ListB)
		return;
	if (this != &ListA && this != &ListB)
		makeEmpty();
	
	Node* left = ListA.head;
	Node* right = ListB.head;
	Node* newNode;
	Node* newHead;
	Node* tempHolder;
	Type* dataPtr;
	if (this == &ListA || this == &ListB) {
		dataPtr = new Type();
		if (this == &ListA)
			*dataPtr = *left->data;
		else
			*dataPtr = *right->data;
		newHead = new Node();
		newHead->data = dataPtr;
		tempHolder = newHead;
		left = left->next;
		right = right->next;
	}
	else
		{
		makeEmpty();
		dataPtr = new Type();
		*dataPtr = *left->data;
		newHead = new Node();
		newHead->data = dataPtr;
		tempHolder = newHead;
		left = left->next;
		right = right->next;
	}
	while (left != NULL && right != NULL) {
		if (*left->data == *right->data) { // if match add to list
			dataPtr = new Type();
			*dataPtr = *left->data;
				newNode = new Node();
				newNode->data = dataPtr;
				newHead->next = newNode;
				newHead = newHead->next;
			
			left = left->next;
			right = right->next;
		}
		else if (*left->data < *right->data) { // if at end of list, stop
			if (left->next == NULL)              // otherwise walk down list
				break;
			else
				left = left->next;
		}
		else {
			if (right->next == NULL)             // same logic as previous
				break;                           // case, but with different
			else                                 // pointer
				right = right->next;
		}
	}
	makeEmpty();
	head = tempHolder;
}

//----------------------------------------------------------------------------
// isEmpty()
// Description: check to see if List is empty
template <typename Type>
bool List<Type>::isEmpty() const {
	return head == NULL;
}

//----------------------------------------------------------------------------
// makeEmpty()
// Description: clears a list of all nodes and data
template <typename Type>
void List<Type>::makeEmpty() {
	if (head != NULL) {
		Node* nodeNext;
		while (head->next != NULL) { // walk the list, deleting nodes
			nodeNext = head->next;
			if (head->data != NULL) {
				delete head->data;
				head->data = NULL;
			}
			delete head;
			head = NULL;
			head = nodeNext;
		}
		// off-by-one check for the last node in list
		if (head != NULL && head->data != NULL) {
			delete head->data;
			head->data = NULL;
		}
		if (head != NULL) {
			delete head;
			head = NULL;
		}
	}
}

//----------------------------------------------------------------------------
// operator=
// Description: assigns this list a deep copy of the right list
template <typename Type>
List<Type>& List<Type>::operator=(const List<Type>& right) {
	if (right.head == NULL) {
		makeEmpty();
		head = NULL;
		return *this;
	}
	if (&right != this) {            // check for self assignment
		makeEmpty();
		head = new Node();           // off by one copy check for head
		Node* oPtr = right.head;
		Type* dataPtr = new Type();
		*dataPtr = *oPtr->data;
		head->data = dataPtr;
		Node* lastPtr = head;
		while (oPtr->next != NULL) { // copy right's list remaining nodes
			oPtr = oPtr->next;
			Type* nestedDataPtr = new Type();
			*nestedDataPtr = *oPtr->data;
			Node* newNodePtr = new Node();
			newNodePtr->data = nestedDataPtr;
			lastPtr->next = newNodePtr;
			lastPtr = lastPtr->next;
		}
		lastPtr->next = NULL;
	}
	return *this;
}

//----------------------------------------------------------------------------
// operator==
// Description: return true if both lists are a match
template <typename Type>
bool List<Type>::operator==(const List<Type>& right) const {
	if ((this == &right) || (head == NULL && right.head == NULL)) {
		return true;
	}
	Node* curr = head;
	Node* other = right.head;
	if ((curr == NULL && other != NULL) ||
		(curr != NULL && other == NULL) ||
		(*curr->data != *other->data)) {
		return false;
	}
	// return false on the first non-matching data
	while (curr->next != NULL && other->next != NULL) {
		if (*curr->data != *other->data)
			return false;
		curr = curr->next;
		other = other->next;
	}
	return true;
}

//----------------------------------------------------------------------------
// operator!=
// Description: return true if both lists are not a match.  Uses the
//              opposite logic of the operator==
template <typename Type>
bool List<Type>::operator!=(const List<Type>& right) const {
	return !(*this == right);
}

#endif