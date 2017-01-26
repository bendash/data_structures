/**
 * Doubly Linked List Data Structure
 *
 * Header File
 *
 * (c) Ben Walch, 2016
 */

#ifndef DLIST_H
#define DLIST_H

// using 'typedef' makes things more convinient
// we define hereby a new data type 'node'
typedef struct DoublyLinkedListNode dlist_node;
struct DoublyLinkedListNode {
    void* value;
    dlist_node* prev;
    dlist_node* next;
};

typedef struct DoublyLinkedList dlist;
struct DoublyLinkedList {
    int size;
    dlist_node* first;
    dlist_node* last;
};

// creates a node
// this is used as the list 'container'
// which all further functions expect as param
dlist* dlist_create();

// destroys the list and 
// frees up memory
void dlist_destroy(dlist* list);

// check if the list is empty
int dlist_is_empty(dlist* list);

// returns the list's size
int dlist_size(dlist* list);

// appends an element to the list
void dlist_append(dlist* list, void* el);

// prepends an element to the list
void dlist_prepend(dlist* list, void* el);

// pops an element from the list
void* dlist_pop(dlist* list);

// gets element at specific index
void* dlist_get(dlist* list, int index);

// inserts an element at specific index
void dlist_insert(dlist* list, int index, void* el);

// removes an element at specific index
void* dlist_remove(dlist* list, int index);

// returns 1 if element is in the list, 0 otherwise
int dlist_contains(dlist* list, void* el, int (*cmp)(const void*, const void*));

// returns the position of the element
int dlist_index_of(dlist* list, void* el, int (*cmp)(const void*, const void*));

// sorts the list
void dlist_sort(dlist* list, int (*cmp)(const void *, const void *));

#endif
