/**
 * Hashtable (seperate chained) Data Structure
 *
 * Header File
 *
 * (c) Ben Walch, 2016
 */

#ifndef HASHTABLE_H
#define HASHTABLE_H

#define HASHTABLE_INITIAL_SIZE 10

#include <stdlib.h>

typedef struct HashTableEntry hashtable_entry;
struct HashTableEntry {
    char* key;
    void* value;
    hashtable_entry* next;
};

typedef struct HashTable hashtable;
struct HashTable {
    int size;
    hashtable_entry** table;
};

/* creates an empty hashtable of size hashtable_size */
extern hashtable* hashtable_create();

/* creates an empty hashtable of size hashtable_size */
extern hashtable* hashtable_create_size(int hashtable_size);

/* destroys the hashtables and frees allocated memory */
extern void hashtable_destroy(hashtable* ht);

/* puts an element with a key into the hashtable */
extern void hashtable_set(hashtable* ht, char* k, void* v);

/* removes the element with the key from the hashtable */
extern void* hashtable_remove(hashtable* ht, char* k);

/* gets an element from the hashtable if it exists */
extern void* hashtable_get(hashtable* ht, char* key);

/* returns 1 if an element for the key is found, 0 otherwise */
extern int hashtable_contains(hashtable* ht, char* key);

#endif
