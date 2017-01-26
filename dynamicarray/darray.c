/**
 * Dynamic Array Data Structure
 *
 * Implementation File
 *
 * (c) Ben Walch, 2016
 */

#include <stdio.h>
#include <stdlib.h>

#include "darray.h"

int _darray_ensure_capacity(darray* da, int min_capacity) {
    if (min_capacity > da->size) {
        da->capacity += da->capacity/2;
        if ((da->data = realloc(da->data, da->capacity*sizeof(void*))) == NULL) {
            return 0;
        }
    }
    return 1;
}

int _darray_index_check(darray* da, int index) {
    if (index < 0 || index >= da->size) {
        return 0;
    }
    return 1;
}

void _darray_swap(darray* da, int i1, int i2) {
   void* t = da->data[i1];
   da->data[i1] = da->data[i2];
   da->data[i2] = t;
}

darray* darray_create() {
    return darray_create_capacity(DARRAY_INITIAL_CAPACITY);
}

darray* darray_create_capacity(int capacity) {
	
    /* create array handle */
	darray* da = malloc(sizeof(darray));
	if (!da) {
		return NULL;
	}

	/* initial size */
	da->size = 0;

	/* initial capacity */
	da->capacity = capacity;
	da->data = malloc(sizeof(void*)*da->capacity);
	if (!da->data) {
		return NULL;
	}

	return da;
}

void darray_destroy(darray* da) {
    free(da->data);
    free(da);
}

int darray_is_empty(darray* da) {
    return (da->size == 0);
}

int darray_size(darray* da) {
	return da->size;
}

void darray_append(darray* da, void* el) {
    if (_darray_ensure_capacity(da, da->size+1)) {
        da->data[da->size++] = el;
    }
}

void darray_prepend(darray* da, void* el) {
    darray_insert(da, 0, el);
}

void darray_insert(darray* da, int index, void* el) {
    if (!_darray_index_check(da, index)) {
        return;
    }
    if (_darray_ensure_capacity(da, da->size+1)) {
        // move other elements around
        for (int i = da->size-1; i >= index; i--) {
            da->data[i+1] = da->data[i];    
        }

        // insert element
        da->data[index] = el;
        da->size++;
    }
}

void* darray_remove(darray* da, int index) {
    if (!_darray_index_check(da, index)) {
        return NULL;
    }
    void* temp = da->data[index];
    // move other elements around
    for (int i = index; i < da->size-1; i++) {
        da->data[i] = da->data[i+1];
    }
    da->size--;
    return temp;
}

void* darray_pop(darray* da) {
    return darray_remove(da, da->size-1);
}

void* darray_get(darray* da, int index) {
    return da->data[index];
}

void darray_set(darray* da, int index, void* el) {
    if (_darray_index_check(da, index)) {
        da->data[index] = el;
    }
}

int darray_index_of(darray* da, void* el, int (*cmp)(const void*, const void*)) {
    for (int i = 0; i < da->size; i++) {
        if ((*cmp)(da->data[i], el) == 0) {
            return i;
        }
    }
    return -1;
}

int darray_contains(darray* da, void* el, int (*cmp)(const void*, const void*)) {
    return (darray_index_of(da, el, cmp) >= 0);
}

void darray_sort(darray *da, int (*cmp)(const void*, const void*)) {
    void* t;
    for (int i = 0; i < da->size; i++) {
        for (int j = 0; j < da->size-1; j++) {
            if (cmp(da->data[j+1], da->data[j]) < 0) {
                _darray_swap(da, j, j+1);
            }
        }
    }
    // qsort(da->data, da->size, sizeof(void*), cmp);
}
