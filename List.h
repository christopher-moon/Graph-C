//Christopher Moon
//ckmoon
//pa2

#ifndef __LINKEDLIST_H__
#define __LINKEDLIST_H__
//#include "Graph.h"

typedef struct ListObj* List;

List newList(void); 

void freeList(List* pL);

// Access functions -----------------------------------------------------------
int length(List L); // Returns the number of elements in L.
int index(List L); // Returns index of cursor element if defined, -1 otherwise.
int front(List L); // Returns front element of L. Pre: length()>0
int back(List L); // Returns back element of L. Pre: length()>0
int get(List L); // Returns cursor element of L. Pre: length()>0, index()>=0
bool equals(List A, List B); 

// Returns true if Lists A and B are in same  state, and returns false otherwise.

// Manipulation procedures ----------------------------------------------------
void clear(List L); // Resets L to its original empty state.
void set(List L, int x); // Overwrites the cursor element’s data with x.
 // Pre: length()>0, index()>=0
void moveFront(List L); // If L is non-empty, sets cursor under the front element,
 // otherwise does nothing.
void moveBack(List L); // If L is non-empty, sets cursor under the back element,
 // otherwise does nothing.
void movePrev(List L); // If cursor is defined and not at front, move cursor one
 // step toward the front of L; if cursor is defined and at
 // front, cursor becomes undefined; if cursor is undefined
 // do nothing
void moveNext(List L); // If cursor is defined and not at back, move cursor one
 // step toward the back of L; if cursor is defined and at
 // back, cursor becomes undefined; if cursor is undefined
 // do nothing
void prepend(List L, int x); // Insert new element into L. If L is non-empty,
 // insertion takes place before front element.
void append(List L, int x); // Insert new element into L. If L is non-empty,
 // insertion takes place after back element.
void insertBefore(List L, int x);

void insertAfter(List L, int x);

void printList(FILE* out, List L);

void deleteFront(List L);

void deleteBack(List L);

void delete(List L);

List copyList(List L);

#endif
