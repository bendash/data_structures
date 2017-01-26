/**
 * Hashtable (seperate chained) Data Structure
 *
 * Header File
 *
 * (c) Ben Walch, 2016
 :*/

#include <stdio.h>
#include <string.h>

#include "hashtable.h"

// hash function implementations
// alter hashtable_hash function
// to decide which of them to use

// Fowler-Noll-Vo
// https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function
#define FNV_PRIME 16777619
#define FNV_OFFSET_BASIS 2166136261 
unsigned int hash_fnv(const char *key) {
    unsigned int hash = FNV_OFFSET_BASIS;
    for (unsigned int i = 0; key[i] != 0; i++) {
        hash = hash * FNV_PRIME;
        hash = hash ^ key[i];
    }
    return hash;
}

// Jenkins
// https://en.wikipedia.org/wiki/Jenkins_hash_function
unsigned int hash_jenkins(const char* key) {
    unsigned int hash, i;
    for (hash = i = 0; key[i] != 0; i++) {
        hash += key[i];
        hash += (hash << 10);
        hash ^= (hash >> 6);   
    }
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return hash;
}

// simple hashing
// for each character in key, shift 8 and add ASCII code
unsigned int hash_simple(const char* key) {
    unsigned int hash, i;
    for (hash = i = 0; key[i] != 0; i++) {            
        hash = hash << 8;      
        hash += key[i];
    }
    return hash;
}

// creates a hashtable pointer and allocates all stuff
hashtable* hashtable_create_size(int hashtable_size) {
    
    if (hashtable_size <= 0) {
        // invalid size
        return NULL;
    }

    hashtable* ht;

    // allocate hashtable
    if ((ht = malloc(sizeof(hashtable))) == NULL) {
        perror("failed to allocate memory for hashtable");
        return NULL;
    }

    // set size
    ht->size = hashtable_size;

    // allocate internal nodes array
    if ((ht->table = calloc(ht->size, sizeof(hashtable_entry*))) == NULL) {
        perror("failed to allocate memory for hashtable buckets");
        return NULL;
    }

    return ht;
}

hashtable* hashtable_create() {
    return hashtable_create_size(HASHTABLE_INITIAL_SIZE);
}

// destroys a hashtable and frees all stuff
void hashtable_destroy(hashtable* ht) {
    for (int i = 0; i < ht->size; i++) {
        if (ht->table[i] != NULL) {
            hashtable_entry* iterator = ht->table[i];
            while (iterator != NULL) {
                hashtable_entry* temp = iterator;
                iterator = iterator->next;
                free(temp->key);
                free(temp);
            }
        }
    }
    free(ht->table);
    free(ht);
}

// the hashing function
int hashtable_hash(hashtable* ht, char* key) {
    unsigned int hashed_key = hash_jenkins(key);
    return hashed_key % ht->size;
}

// puts an element with a key into the hash table
void hashtable_set(hashtable* ht, char* key, void* v) {
    unsigned int hash = hashtable_hash(ht, key);
    hashtable_entry* iterator;
    hashtable_entry* prev;
    hashtable_entry* new_entry;

    iterator = ht->table[hash];

    // scan nodes in this bucket.
    // either we have to replace the value (if the key is the same)
    // or we have to attach the new node after the last one 
    while (iterator != NULL && strcmp(key, iterator->key) != 0) {
        prev = iterator;
        iterator = iterator->next;    
    }

    // if we are not at the end, we know that there exists
    // an entry with the same key, replace its value
    if (iterator != NULL && strcmp(key, iterator->key) == 0) {
        free(iterator->value);
        iterator->value = v;
    // there is no entry with the same key, create a new entry
    } else {

        if ((new_entry = malloc(sizeof(hashtable_entry))) == NULL) {
            perror("failed to allocate memory for the new entry");
            return;
        }

        // duplicate the key
        if ((new_entry->key = strdup(key)) == NULL) {
            perror("failed to allocate memory for the new key");
            return;
        }
        new_entry->value = v;
        new_entry->next = NULL;
      
        if (ht->table[hash] == NULL) {
            // we are at the start of the list
            ht->table[hash] = new_entry;
        } else {
            // we are at the end of the list
            prev->next = new_entry;
        }
    }
}

void* hashtable_remove(hashtable* ht, char* key) {
    void* t;
    unsigned int hash = hashtable_hash(ht, key);
    hashtable_entry* iterator = ht->table[hash];
        
    // go through the nodes in the bucket and compare the key of each node
    // if it matches, return node's data
    while (iterator != NULL && strcmp(key, iterator->key) != 0) {
        iterator = iterator->next;
    }

    if (iterator == NULL) {
        return NULL;
    }
    t = iterator->value;
    free(iterator);
    return t; 
}

void* hashtable_get(hashtable* ht, char* key) {
    unsigned int hash = hashtable_hash(ht, key);
    hashtable_entry* iterator = ht->table[hash];
        
    // go through the nodes in the bucket and compare the key of each node
    // if it matches, return node's data
    while (iterator != NULL && strcmp(key, iterator->key) != 0) {
        iterator = iterator->next;
    }

    if (iterator == NULL) {
        return NULL;
    }
    return iterator->value;                                   
}

int hashtable_contains(hashtable* ht, char* key) {
    return (hashtable_get(ht, key) != NULL);
}
