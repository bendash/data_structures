/**
 * Singly Linked List Data Structure
 *
 * Implementation File
 *
 * (c) Ben Walch, 2016
 */

#include <stdio.h>
#include <stdlib.h>

#include "slist.h"

int _slist_index_check(slist* list, int index) {
    if (index < 0 || index >= list->size) {
        return 0;
    }
    return 1;
}

slist* slist_create() {
    
    slist* list = malloc(sizeof(slist));
    if (!list) {
        return NULL;
    }

    list->size = 0;
    list->first = NULL;
    list->last = NULL;
    
    return list;
}

void slist_destroy(slist* list) {
    // we want to free up nodes from
    // the start of the list to end
    slist_node* iterator = list->first;
    while(iterator != NULL) {
        slist_node *tmp = iterator;
        iterator = iterator->next;
        free(tmp);
    }

    // at the end, we can free our list handle
    free(list);
}

int slist_is_empty(slist* list) {
    return list->size == 0;
}

int slist_size(slist* list) {
    return list->size;
}

void slist_append(slist* list, void* el) {

    // allocate new memory for new element
    slist_node* newnode = malloc(sizeof(slist_node));
    if (!newnode) {
        return;
    }
    
    // set values
    newnode->value = el;
    newnode->next = NULL;

    // attach the new node to the list
    if (slist_is_empty(list)) {
        list->first = newnode;
    } else {
        list->last->next = newnode;
    }
    list->last = newnode;
    list->size++;
}

void slist_prepend(slist* list, void* el) {
     // allocate new memory for new element
    slist_node* newnode = malloc(sizeof(slist_node));
    if (!newnode) {
        return;
    }
    
    // set values
    newnode->value = el;
    newnode->next = NULL;
    
    // attach it to the beginning of the list
    if (slist_is_empty(list)) {
        list->last = newnode;
    } else {
        newnode->next = list->first;
    }
    list->first = newnode;
    list->size++;
}

void* slist_pop(slist* list) {
    return slist_remove(list, list->size-1);
}

void slist_insert(slist* list, int index, void* el) {
    // check if index is valid
    if (!_slist_index_check(list, index)) {
        // invalid index!
        return;
    }
    // check if index is first or last
    // to make use of existing functions
    if (index == 0) {
        slist_prepend(list, el);
        return;
    } else if (index == list->size-1) {
        slist_append(list, el);
        return;
    } else {
        // otherwise, find the node before the one with 
        // the index we want to insert
        slist_node* iterator = list->first;
        for (int i = 0; i < index-1; i++) {
            iterator = iterator->next;
        }

        slist_node* newnode = malloc(sizeof(slist_node));
        newnode->value = el;

        // attach it
        newnode->next = iterator->next;
        iterator->next = newnode;
        
        // increase size
        list->size++;
    }
}

void* slist_get(slist* list, int index) {
    // check if index is valid
    if (!_slist_index_check(list, index)) {
        // invalid index!
        return NULL;
    }
    // go through the list, stop if index equals our counter or list has reached end
    slist_node* iterator = list->first;
    for (int i = 0; i < index; i++) {
        iterator = iterator->next;
    }
    // after the loop we have in iterator stored the node at desired index 
    return iterator->value;
}

void* slist_remove(slist* list, int index) {
    slist_node* temp;
    void* t;
    if (!_slist_index_check(list, index)) {
        // invalid index!
        return NULL;
    }
    if (index == 0) {
        temp = list->first;
        list->first = temp->next;
    } else { 
        // get the node before the index of 
        // the node to remove
        slist_node* iterator = list->first;
        for (int i = 0; i < index-1; i++) {
            iterator = iterator->next;
        }
        temp = iterator->next;
        iterator->next = temp->next;
    }
    list->size--;
    t = temp->value;
    free(temp);
    return t;
}
