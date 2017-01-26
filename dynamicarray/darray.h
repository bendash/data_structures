/**
 * Dynamic Array Data Structure
 *
 * Header File
 *
 * (c) Ben Walch, 2016
 */

#ifndef DARRAY_H
#define DARRAY_H

#define DARRAY_INITIAL_CAPACITY 10

typedef struct DynamicArray {
	// number of elements in the array
    int size;         
    // number of elements the array can hold
	int capacity;
    // pointer to the underlying array
	void** data;
} darray;

// returns an empty array with given capacity or NULL on failure
darray* darray_create_capacity(int capacity);

// returns an empty array with some initial capacity or NULL on failure
darray* darray_create(void);

// free all allocated memory segments of the array
void darray_destroy(darray* da);

// check if array is empty
int darray_is_empty(darray* da);

// return the current number of elements
int darray_size(darray* da);

// append a new element to the array
void darray_append(darray* da, void* el);

// prepend a new element to the array
void darray_prepend(darray* da, void* el);

// insert a new element on the array
void darray_insert(darray* da, int index, void* el);

// remove element of the array
void* darray_remove(darray* da, int index);

// pop element
void* darray_pop(darray* da);

// get element at index
void* darray_get(darray* da, int index);

// set element at index
void darray_set(darray* da, int index, void* el);

// check if element is contained in array
int darray_contains(darray* da, void* el, int (*cmp)(const void*, const void*));

// search for an element
int darray_index_of(darray* da, void* el, int (*cmp)(const void*, const void*));

// sorts the array
void darray_sort(darray* da, int (*cmp)(const void*, const void*));

#endif
