//Sean Song CMPS101 pa1 25/7/19 README README
#ifndef _INTLIST_H_INCLUDE_
#define _INTLIST_H_INCLUDE_
#endif

typedef struct ListObj *List;

// Constructors-Destructors ---------------------------------------------------
List newList(void);			 // Creates and returns a new empty List.
void freeList(List *pL); // Frees all heap memory associated with *pL, and sets *pL to NULL.

// Access functions -----------------------------------------------------------
int length(List L); // Returns the number of elements in L.
int index(List L);	// Returns index of cursor element if defined, -1 otherwise.
int front(List L);	// Returns front element of L. Pre: length()>0
int back(List L);		// Returns back element of L. Pre: length()>0
void *get(List L);	// Returns cursor element of L. Pre: length()>0, index()>=0
// int equals(List A, List B); // Returns true (1) iff Lists A and B are in same state, and returns false (0) otherwise.

// Manipulation procedures ----------------------------------------------------
void clear(List L);													// Resets L to its original empty state.
void moveFront(List L);											// If L is non-empty, sets cursor under the front element,
																						// otherwise does nothing.
void moveBack(List L);											// If L is non-empty, sets cursor under the back element,
																						// otherwise does nothing.
void movePrev(List L);											// If cursor is defined and not at front, move cursor one
																						// step toward the front of L; if cursor is defined and at
																						// front, cursor becomes undefined; if cursor is undefined
																						// do nothing
void moveNext(List L);											// If cursor is defined and not at back, move cursor one
																						// step toward the back of L; if cursor is defined and at
																						// back, cursor becomes undefined; if cursor is undefined
																						// do nothing
void prepend(List L, void *data);						// Insert new element into L. If L is non-empty,
																						// insertion takes place before front element.
void append(List L, void *data);						// Insert new element into L. If L is non-empty,
																						// insertion takes place after back element.
void insertBefore(List L, void *data);			// Insert new element before cursor.
																						// Pre: length()>0, index()>=0
void insertAfter(List L, void *data);				// Insert new element before cursor.
																						// Pre: length()>0, index()>=0
void *getAt(List L, int key);								// Get key
void insertAt(List L, int key, void *data); // Insert with custom key
void deleteFront(List L);										// Delete the front element. Pre: length()>0
void deleteBack(List L);										// Delete the back element. Pre: length()>0
void delete (List L);												// Delete cursor element, making cursor undefined.
																						// Pre: length()>0, index()>=0
