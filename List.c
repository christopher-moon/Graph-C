//Christopher Moon
//ckmoon
//pa2

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "List.h"


//node 
typedef struct NodeObj{
  
  //value of the int
  int value;
  
  //pointer to next node in the list
  struct NodeObj* prev;
  
  //pointer to previous node
  struct NodeObj* next;
  
}NodeObj;

typedef NodeObj* Node; 

//node constructor
Node node_create(int value){

  //allocate mem
  Node n = malloc( sizeof(NodeObj) );
  
  if(n){  
  
    n->prev = NULL;
    
    n->next = NULL;
    
    n->value = value;
  
  }else{
  
    free(n);
    
    n = NULL;
  
  }
  
  return n;

}

//node delete
void node_delete(Node* n){
  
  //free and null node pointers
  //free(n->next);
  //n->next = NULL;
  //free(n->prev);
  //n->prev = NULL;
  
  //free and null node
  if( n!=NULL && *n!=NULL ){
  
      free(*n);
      
      *n = NULL;
      
   }

}

//linked list
typedef struct ListObj{

  Node front;
  
  Node back;
  
  Node cursor; 
  
  int length;
  
  int index;

}ListObj;

//list constructor
List newList(void){

  List l = malloc( sizeof(ListObj) );
  
  if(l){
  
    l->front = NULL;
    
    l->back = NULL;
    
    l->cursor = NULL;
    
    l->length = 0;
    
    l->index = -1; 
  
  }else{
  
    free(l);
    
    l= NULL;
  
  }
  
  return l;
  
}

//deconstructor
void freeList(List *pL){

  if(pL!=NULL && *pL!=NULL){ 
  
    while(length(*pL) != 0){ 
      
      deleteFront(*pL); 
      
    }
    
    free(*pL);
    
    *pL = NULL;
    
   }

}

//return length
int length(List L){

  if( L==NULL ){
  
      printf("List Error: calling length() on NULL list reference\n");
      
      exit(1);
  }
  
  return (L->length);

}

//return index
int index(List L){

  if( L==NULL ){
  
      printf("List Error: calling index() on NULL list reference\n");
      
      exit(1);
  }
  
  return(L->index);

}

//return front
int front(List L){

  if( L==NULL ){
  
      printf("List Error: calling front() on NULL list reference\n");
      
      exit(1);
  }
  
  if(L->length > 0){
    
    return(L->front->value);
  
  }
  
  exit(1);
  
}

//return back
int back(List L){

  if( L==NULL ){
  
      printf("List Error: calling back() on NULL list reference\n");
      
      exit(1);
  }
  
  if(L->length > 0){
    
    return(L->back->value);
  
  }
  
  exit(1);

  
}

//return cursor node value
int get(List L){

  if( L==NULL ){
  
      printf("List Error: calling get() on NULL list reference\n");
      
      exit(1);
  }
  
  if(L->length > 0 && L->index >= 0){
    
    return(L->cursor->value);
  
  }
  
  exit(1);
  
}

//checks if two lists are equal
bool equals(List A, List B){

  if( A==NULL || B==NULL ){
  
      printf("List Error: calling equals() on NULL list reference\n");
      
      exit(1);
  }
  
  //if not same length, automatically false
  if(A->length != B->length){
  
    return false;
  
  }
  
  //temp nodes for comparison, set as beginning nodes of both lists
  Node a  = A->front;
  
  Node b  = B->front;
  
  while(a != NULL){
    
    //if the equivalent nodes dont have the same numerical value, false
    if(a->value != b->value){
      
      node_delete(&a);
      node_delete(&b);
      return false;
    
    }
    
    //update nodes
    a = a->next;
    b = b->next;
    
  }
  
  node_delete(&a);
  node_delete(&b);
  
  return true;
  
}

//clear
void clear(List L){

  if( L==NULL ){
  
      printf("List Error: calling clear() on NULL list reference\n");
      
      exit(1);
  }
  
  //printf("pass initial condition\n");
  
  //while(length(L) != 0){
    
    //printf("length %d\n", length(L));
    //deleteFront(L);
  
  //}
  
  //printf("pass while\n");
  
  //L->cursor = NULL;
  
  //L->index = -1;
  
  freeList(&L);
  
  L= newList();

}

//set cursor value to x
void set(List L, int x){

  if( L==NULL ){
  
      printf("List Error: calling set() on NULL list reference\n");
      
      exit(1);
  }

  if(L->length > 0 && L->index >= 0){
  
    L->cursor->value = x;
  
  }
  
  exit(1);

}

//set cursor to front, if l is non empty
void moveFront(List L){

  if( L==NULL ){
  
      printf("List Error: calling movefront() on NULL list reference\n");
      
      exit(1);
  }

  if(L->length > 0){
  
    L->cursor = L->front; 
    
    //index starts at 0
    L->index  = 0;
  
  }

}

//set cursor to back
void moveBack(List L){

  if( L==NULL ){
  
      printf("List Error: calling moveback() on NULL list reference\n");
      
      exit(1);
  }

  if(L->length > 0){
  
    L->cursor = L->back; 
    
    L->index  = L->length-1;
  
  }

}

//move cursor back 1
void movePrev(List L){

  if( L==NULL ){
  
      printf("List Error: calling moveprev() on NULL list reference\n");
      
      exit(1);
  }
  
  //cursor defined and not at front
  if(L->cursor != NULL && L->index > 0){
  
    //move cursor back 1
    L->cursor = L->cursor->prev;
    
    L->index--; 
  
  //else if cursor is defined (and at front)
  }else if(L->cursor != NULL && L->index == 0){
  
    L->cursor = NULL;
    
    L->index = -1;
  
  }
  
}

//move cursor forward 1
void moveNext(List L){

  if( L==NULL ){
  
      printf("List Error: calling movenext() on NULL list reference\n");
      
      exit(1);
  }
  
  //cursor defined and not at back
  if(L->cursor != NULL && L->index != L->length-1){
  
    //move cursor back 1
    L->cursor = L->cursor->next;
    
    L->index++; 
  
  //else if cursor is defined (and at back)
  }else if(L->cursor != NULL && L->index == L->length-1){
  
    L->cursor = NULL;
    
    L->index = -1;
  
  }
  
}

//prepend a node into the linked list (front)
void prepend(List L, int x){

  if( L==NULL ){
  
      printf("List Error: calling prepend() on NULL list reference\n");
      
      exit(1);
  }
  
  Node temp = node_create(x);
  
  //if empty, front and back are both x
  if(L->length == 0){
  
    L->front=temp;
    
    L->back=temp;
    
    L->length++;
    
    //node_delete(&temp);
  
  }else{
  
    //temp node points to front node
    temp->next = L->front;
  
    //front prev is now temp
    L->front->prev = temp;
  
    //temp is new front
    L->front = temp; 
  
    //update length
    L->length++;
  
    //update cursor
    if(L->index != -1){
  
      L->index++;
  
    }
  
  }
  
  //node_delete(&temp);

}

//append a node into the linked list (back)
void append(List L, int x){

  if( L==NULL ){
  
      printf("List Error: calling append() on NULL list reference\n");
      
      exit(1);
  }
  
  //CREATE NODE WITH VALUE X
  Node temp = node_create(x);
  
  //if empty, front and back are both x
  if(L->length == 0){
  
    L->front = temp;
    
    L->back = temp;
    
    L->length++;
    
    //node_delete(&temp);
  
  }else{
  
    //temp node points back to back node
    temp->prev = L->back;
  
    //back next is now temp
    L->back->next = temp;
  
    //temp is new front
    L->back = temp; 
  
    //update length
    L->length++;
  
  }
  
  //node_delete(&temp);

}

//insert x before cursor
void insertBefore(List L, int x){

  if( L==NULL ){
  
      printf("List Error: calling insertbefore() on NULL list reference\n");
      
      exit(1);
  }

  if(L->length > 0 && L->index >= 0 && L->cursor != NULL){
    
    //if the the cursor is the first element in the array
    if(L->cursor == L->front){
      
      //prepend
      prepend(L, x);
    
    }else{
    
      //create node with value x
      Node temp = node_create(x);
    
      //temp node stores the node that used to be before cursor 
      temp->prev = L->cursor->prev;
    
      //cursor now comes after temp
      temp->next = L->cursor;
    
      //node that used to be before cursor now points forward to temp
      L->cursor->prev->next = temp;
    
      //cursor prev is temp
      L->cursor->prev = temp;
    
      //increment stats
      L->length++;
    
      L->index++;
      
    
    }
  
  }else{
  
    exit(1);
  
  }

}

//insert x after cursor
void insertAfter(List L, int x){

  if( L==NULL ){
  
      printf("List Error: calling insertafter() on NULL list reference\n");
      
      exit(1);
  }

  if(L->length > 0 && L->index >= 0 && L->cursor != NULL){
    
    //if the the cursor is the last element in the array
    if(L->cursor  == L->back){
      
      //append
      append(L, x);
    
    }else{
    
      //create node with value x
      Node temp = node_create(x);
      
      //reverse of insertBefore
      temp->next = L->cursor->next;
    
      temp->prev = L->cursor;
    
      L->cursor->next->prev = temp;
    
      L->cursor->next = temp;
    
      L->length++;
    
      //L->index++;
    
    }
  
  }else{
  
    exit(1);
  
  }

}

//print 
void printList(FILE* out, List L){

  if( L==NULL ){
  
      printf("list Error: calling print() on NULL list reference\n");
      
      exit(1);
  }
  
  Node temp = L->front;
  
  for(int i =0; i< L->length; i ++){
    
    fprintf(out, "%d ", temp->value);
    
    temp = temp->next;
  
  }
  
  node_delete(&temp);
  
}

//delete front
void deleteFront(List L){

  if( L==NULL ){
  
      printf("List Error: calling deletefront() on NULL list reference\n");
      
      exit(1);
  }
  
  if(L->length > 0){
  
    if(L->length == 1){
  
      node_delete(&L->front);
    
      L->front = NULL;
      
      L->back = NULL;
      
      L->cursor = NULL;
    
      L->index = -1;
    
      L->length = 0;
    
    }else{
    
      //save front value as a temp
      Node temp = L->front;
  
      L->front = L->front->next;
    
      //free original front
      node_delete(&temp);
    
      L->front->prev = NULL;
    
      //mod stats
      L->length--;
    
      if(L->index == 0){
    
        L->index = -1;
       
        L->cursor = NULL;
       
      }else{
    
        L->index--;
      
      }
    
    }
  
  }else{
    printf("terminate deletefront\n");  
    exit(1);
  
  }

}

//delete back
void deleteBack(List L){

  if( L==NULL ){
  
      printf("List Error: calling deletefront() on NULL list reference\n");
      
      exit(1);
  }
  
  if(L->length > 0){
  
    if(L->length == 1){
  
      node_delete(&L->front);
    
      L->front = NULL;
      
      L->back = NULL;
      
      L->cursor = NULL;
    
      L->index = -1;
    
      L->length = 0;
    
    }else{
    
      //save front value as a temp
      Node temp = L->back;
  
      L->back = L->back->prev;
    
      L->back->next = NULL;
    
      //mod stats
      L->length--;
    
      if(L->cursor == temp){
    
        L->index = -1;
       
        L->cursor = NULL;
       
      }
      
      //free original front
      node_delete(&temp);
    
    }
  
  }else{
    
    exit(1);
  
  }

}
//delete cursor
void delete(List L){

  if( L==NULL ){
  
      printf("List Error: calling delete() on NULL list reference\n");
      
      exit(1);
  }
  
  if(L->length >0 && L->index >= 0){
    
    //check if cursor is definied
    if(L->index == -1){
    
      exit(1);
    
    }
    
    //if L is only one element, which is also the cursor, then just reset the list
    if(L->length == 1){
    
      clear(L);
    
    //if cursopr is front
    
    }else if(L->cursor == L->front){
    
      Node temp = L->front;
      
      L->front = L->front->next;
      
      node_delete(&temp);
      
      L->front->prev = NULL;
      
      L->length--;
    
    }
    
    //if cursor is back
    else if(L->cursor == L->back){
    
      Node temp = L->back;
      
      L->back = L->back->prev;
      
      node_delete(&temp);
      
      L->back->next = NULL;
      
      L->length--;
    
    }else{
    
      //default case then
      Node temp = L->cursor;
    
      temp->prev->next = temp->next;
    
      temp->next->prev = temp->prev;
    
      node_delete(&temp);
      
      L->length--;
    
    }
    
    //stats
    
    L->index = -1;
   
  }

}

//copy
List copyList(List L){

  if( L==NULL ){
  
      printf("List Error: calling copy on NULL list reference\n");
      
      exit(1);
  }
  
  List L2 = newList();
  
  Node N = L->front;
  while(N != NULL)
  {
    append(L2, N->value);
    N = N->next;
  }

  return L2;
  
}


  

