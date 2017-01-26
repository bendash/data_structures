/**
 * Doubly Linked List Data Structure
 *
 * Implementation File
 *
 * (c) Ben Walch, 2016
 */

#include <stdio.h>
#include <stdlib.h>

#include "dlist.h"

int _dlist_index_check(dlist* list, int index) {
    if (index < 0 || index >= list->size) {
        return 0;
    }
    return 1;
}

dlist* dlist_create() {
    dlist* list = malloc(sizeof(dlist));

    // initial values
    list->size = 0;
    list->first = NULL;
    list->last = NULL;

    return list;
}

void dlist_destroy(dlist* list) {
    // we want to free up nodes from
    // the start of the list to the end
    dlist_node* iterator = list->first;
    while(iterator != NULL) {
        dlist_node *tmp = iterator;
        iterator = iterator->next;
        free(tmp);
    }

    // at the end, we can free our list handle
    free(list);
}

int dlist_is_empty(dlist* list) {
    return (list->size == 0);
}

int dlist_size(dlist* list) {
    return list->size;
}

void dlist_append(dlist* list, void* el) {
    
    // allocate new memory for new element
    dlist_node* newnode = malloc(sizeof(dlist_node));
    if (!newnode) {
        return;
    }
    
    // set values
    newnode->value = el;
    newnode->next = NULL;
    newnode->prev = NULL;
    
    // attach the new node to the list
    if (dlist_is_empty(list)) {
        list->first = newnode;
    } else {
        list->last->next = newnode;
        newnode->prev = list->last;
    }
    list->last = newnode;
    list->size++;
}

void dlist_prepend(dlist* list, void* el) {
     // allocate new memory for new element
    dlist_node* newnode = malloc(sizeof(dlist_node));
    if (!newnode) {
        return;
    }

    // set values
    newnode->value = el;
    newnode->next = NULL;
    newnode->prev = NULL;

    // attach it to the beginning of the list
    if (dlist_is_empty(list)) {
        list->last = newnode;
    } else {
        newnode->next = list->first;
        list->first->prev = newnode;
    }
    list->first = newnode;
    list->size++;
}

void* dlist_pop(dlist* list) {
    void* t;
    dlist_node* temp = list->last;
    list->last = temp->prev;
    list->last->next  = NULL;
    t = temp->value;
    free(temp);
    return t;
}

void* dlist_get(dlist* list, int index) {
    // check if index is valid
    if (!_dlist_index_check(list, index)) {
        // invalid index!
        return NULL;
    }
    // go through the list, stop if index equals our counter or list has reached end
    dlist_node* iterator = list->first;
    for (int i = 0; i < index; i++) {
        iterator = iterator->next;
    }
    // after the loop we have in iterator stored the node at desired index 
    return iterator->value;
}

void dlist_insert(dlist* list, int index, void* el) {
    // check if index is valid
    if (!_dlist_index_check(list, index)) {
        // invalid index!
        return;
    }
    // check if index is first or last
    // to make use of existing functions
    if (index == 0) {
        dlist_prepend(list, el);
        return;
    } else if (index == list->size) {
        dlist_append(list, el);
        return;
    } else {
        // otherwise, find the node at the index
        // we want to insert
        dlist_node* iterator = list->first;
        for (int i = 0; i < index; i++) {
            iterator = iterator->next;
        }

        // allocate memory for new node
        dlist_node* newnode = malloc(sizeof(dlist_node));
        newnode->value = el;

        // attach it
        newnode->next = iterator;
        newnode->prev = iterator->prev;
        iterator->prev->next = newnode;
        iterator->prev = newnode;
        
        // increase size
        list->size++;
    }
}

void* dlist_remove(dlist* list, int index) {
    void* t;
    dlist_node* temp;
    // check if index is valid
    if (!_dlist_index_check(list, index)) {
        // invalid index!
        return NULL;
    }
    if (index == 0) {
        temp = list->first;
        list->first = temp->next;
        list->first->prev = NULL;
    } else if (index == list->size-1) {
        temp = list->last;
        list->last = temp->prev;
        list->last->next = NULL;
    } else {
        // get the node at the index of 
        // the node to remove
        dlist_node *iterator = list->first;
        for (int i = 0; i < index; i++) {
            iterator = iterator->next;
        }
        // after the loop, iterator is the node we want to remove
        temp = iterator;
        temp->prev->next = temp->next;
        temp->next->prev = temp->prev;
    }
    list->size--;
    t = temp->value;
    free(temp);
    return t;
}

int dlist_contains(dlist* list, void* el, int (*cmp)(const void*, const void*)) {
    return (dlist_index_of(list, el, cmp) != -1);
}

int dlist_index_of(dlist* list, void* el, int (*cmp)(const void*, const void*)) {
    int i = 0;
    dlist_node* iterator = list->first;
    while (iterator != NULL) {
        if (cmp(iterator->value, el) == 0) {
            return i;
        }
        iterator = iterator->next;
        i++;
    }
    return -1;
}

void dlist_sort(dlist* list, int (* cmp)(const void*, const void*)) {
    // start at the second element
    // and iterate until the list end
    dlist_node* iterator = list->first->next;
    while (iterator != NULL) {
        // compare the current element with all previous elements
        dlist_node* temp = iterator;
        while (temp->prev != NULL && (*cmp)(temp->value, temp->prev->value) < 0) {
            // swap element with the previous one
            // if it is greater than the previous one 
            void* t = temp->value;
            temp->value = temp->prev->value;
            temp->prev->value = t;

            temp = temp->prev;
        }
        iterator = iterator->next;
    }
}
