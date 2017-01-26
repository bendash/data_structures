/**
 * Singly Linked List Data Structure
 *
 * Header File
 *
 * (c) Ben Walch, 2016
 */

#ifndef SLIST_H
#define SLIST_H

// define a structure for slist_node
// using 'typedef' makes things more convinient
// we define hereby a new data type 'slist_node'
typedef struct SinglyLinkedListNode slist_node;
struct SinglyLinkedListNode {
	void* value;
	slist_node* next;
};

typedef struct SinglyLinkedList slist;
struct SinglyLinkedList {
   slist_node* first;
   slist_node* last;
   int size;
};

// creates a list which is used
// as 'handle' for all operations
// on the list
slist *slist_create();

// destroys the slist and
// frees the memory
void slist_destroy();

// returns the list's size
int slist_size(slist* list);

// check if the list is empty
int slist_is_empty(slist* list);

// appends an element to the list
void slist_append(slist* list, void* el);

// prepends an element to the list
void slist_prepend(slist* list, void* el);

// pops an element from the list
void* slist_pop(slist* list);

// gets element at specific index
void* slist_get(slist* list, int index);

// inserts an element at specific index
void slist_insert(slist* list, int index, void* el);

// removes an element at specific index
void* slist_remove(slist* list, int index);

#endif
