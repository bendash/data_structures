/**
 * Test file for the datastructures
 *
 * @author Ben Walch
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "dynamicarray/darray.h"

#include "linkedlist/slist.h"
#include "linkedlist/dlist.h"

#include "hashtable/hashtable.h"

#define CLS "\033c"

void test_darray();
void test_slist();
void test_dlist();
void test_hashtable();
void test_tree();

int cmp_func(const void* el1, const void* el2) {
    return *(int*)el1 - *(int*)el2;
}

int main(void) {
    
    int b = 1;
    int choice = 0;
   
    while (b) {
        printf(CLS);

        printf("\n");
        printf("(1)\t Dynamic Array\n");
        printf("(2)\t Singly-linked List\n");
        printf("(3)\t Doubly-linked List\n");
        printf("(4)\t Hashtable\n");
        printf("(5)\t Tree\n");
        printf("(6)\t Exit\n");
        printf("\n");
    
        printf("Choose your data structure: ");

        scanf("%d", &choice);

        switch(choice) {
            case 1: // dynamic array
                test_darray();
                break;
            case 2: // singly-linked list
                test_slist();
                break;
            case 3: // doubly-linked list
                test_dlist();
                break;
            case 4: // hashtable
                test_hashtable();
                break;
            case 5: // tree
                break;
            case 6: // exit
            default:
                b = 0;
                break;
        }
    } 

    return EXIT_SUCCESS;
}

void test_darray() {
    darray* da;
    int* r;
    int b = 1;
    int choice = 0;
    int index = 0;
    int key = 0;

    srand(time(NULL));
    
    da = darray_create();

    for (int i = 0; i < 20; i++) {
        r = malloc(sizeof(int));
        *r = rand() % 200;
        darray_append(da, r);
    }
    
    while (b) {
        printf(CLS);
        printf("\n");
        for (int i = 0; i < da->size; i++) {
            printf("[%d]", *(int*)darray_get(da, i));
        }
        printf("\n");
        printf("\n");
        printf("(1)\tAppend an element\n");
        printf("(2)\tPrepend an element\n");
        printf("(3)\tInsert an element\n");
        printf("(4)\tRemove an element\n");
        printf("(5)\tPop an element\n");
        printf("(6)\tSearch an element\n");
        printf("(7)\tSort the array\n");
        printf("(8)\tExit\n");
        printf("\n");

        printf("What would you like to do? ");

        scanf("%d", &choice);

        switch (choice) {
            case 1: // append
                r = malloc(sizeof(int));
                *r = rand() % 200;
                darray_append(da, r);
                printf("Appended %d.\n", *r);
                break;
            case 2: // prepend
                r = malloc(sizeof(int));
                *r = rand() % 200;
                darray_prepend(da, r);
                printf("Prepended %d.\n", *r);
                break;
            case 3: // insert
                printf("Enter position to insert: ");
                scanf("%d", &index);
                r = malloc(sizeof(int));
                *r = rand() % 200;
                darray_insert(da, index, r);
                printf("Inserted %d at position %d.\n", *r, index);
                break;
            case 4: // remove
                printf("Enter position to remove: ");
                scanf("%d", &index);
                r = darray_remove(da, index);
                printf("removed %d at position %d.\n", *r, index);
                break;
            case 5: // pop
                r = darray_pop(da);
                printf("popped %d.", *r);
                break;
            case 6: // search
                printf("Enter key to search: ");
                scanf("%d", &key);
                if ((index = darray_index_of(da, &key, cmp_func)) != -1) {
                    printf("Found %d at position %d.\n", key, index);
                } else {
                    printf("Did not find %d.", key);
                }
            case 7: // sort
                darray_sort(da, cmp_func);
                break;
            default:
                b = 0;
                break;
        }
    }
    darray_destroy(da);
}

void test_slist() {
    slist* list;
    int* r;
    int b = 1;
    int choice = 0;
    int index = 0;
    int key = 0;

    srand(time(NULL));
    
    list = slist_create();

    for (int i = 0; i < 20; i++) {
        r = malloc(sizeof(int));
        *r = rand() % 200;
        slist_append(list, r);
    }
    
    while (b) {
        printf(CLS);
        printf("\n");
        slist_node* iterator = list->first;
        while(iterator != NULL) {
            printf(" %d ->", *(int*)iterator->value);
            iterator = iterator->next;
        }
        printf("\n");
        printf("\n");
        printf("(1)\tAppend an element\n");
        printf("(2)\tPrepend an element\n");
        printf("(3)\tInsert an element\n");
        printf("(4)\tRemove an element\n");
        printf("(5)\tPop an element\n");
        printf("(6)\tExit\n");
        printf("\n");

        printf("What would you like to do? ");

        scanf("%d", &choice);

        switch (choice) {
            case 1: // append
                r = malloc(sizeof(int));
                *r = rand() % 200;
                slist_append(list, r);
                printf("Appended %d.\n", *r);
                break;
            case 2: // prepend
                r = malloc(sizeof(int));
                *r = rand() % 200;
                slist_prepend(list, r);
                printf("Prepended %d.\n", *r);
                break;
            case 3: // insert
                printf("Enter position to insert: ");
                scanf("%d", &index);
                r = malloc(sizeof(int));
                *r = rand() % 200;
                slist_insert(list, index, r);
                printf("Inserted %d at position %d.\n", *r, index);
                break;
            case 4: // remove
                printf("Enter position to remove: ");
                scanf("%d", &index);
                r = slist_remove(list, index);
                printf("removed %d at position %d.\n", *r, index);
                break;
            case 5: // pop
                r = slist_pop(list);
                printf("popped %d.", *r);
                break;
            default:
                b = 0;
                break;
        }
    }
    slist_destroy(list);
}

void test_dlist() {
    dlist* list;
    int* r;
    int b = 1;
    int choice = 0;
    int index = 0;
    int key = 0;

    srand(time(NULL));
    
    list = dlist_create();

    for (int i = 0; i < 20; i++) {
        r = malloc(sizeof(int));
        *r = rand() % 200;
        dlist_append(list, r);
    }
    
    while (b) {
        printf(CLS);
        printf("\n");
        dlist_node* iterator = list->first;
        while(iterator != NULL) {
            printf(" %d <=>", *(int*)iterator->value);
            iterator = iterator->next;
        }
        printf("\n");
        printf("\n");
        printf("(1)\tAppend an element\n");
        printf("(2)\tPrepend an element\n");
        printf("(3)\tInsert an element\n");
        printf("(4)\tRemove an element\n");
        printf("(5)\tPop an element\n");
        printf("(6)\tSearch an element\n");
        printf("(7)\tSort the list\n");
        printf("(8)\tExit\n");
        printf("\n");

        printf("What would you like to do? ");

        scanf("%d", &choice);

        switch (choice) {
            case 1: // append
                r = malloc(sizeof(int));
                *r = rand() % 200;
                dlist_append(list, r);
                printf("Appended %d.\n", *r);
                break;
            case 2: // prepend
                r = malloc(sizeof(int));
                *r = rand() % 200;
                dlist_prepend(list, r);
                printf("Prepended %d.\n", *r);
                break;
            case 3: // insert
                printf("Enter position to insert: ");
                scanf("%d", &index);
                r = malloc(sizeof(int));
                *r = rand() % 200;
                dlist_insert(list, index, r);
                printf("Inserted %d at position %d.\n", *r, index);
                break;
            case 4: // remove
                printf("Enter position to remove: ");
                scanf("%d", &index);
                r = dlist_remove(list, index);
                printf("removed %d at position %d.\n", *r, index);
                break;
            case 5: // pop
                r = dlist_pop(list);
                printf("popped %d.", *r);
                break;
             case 6: // search
                printf("Enter key to search: ");
                scanf("%d", &key);
                if ((index = dlist_index_of(list, &key, cmp_func)) != -1) {
                    printf("Found %d at position %d.\n", key, index);
                } else {
                    printf("Did not find %d.", key);
                }
                break;
            case 7: // sort
                dlist_sort(list, cmp_func);
                break;
            default:
                b = 0;
                break;
        }
    }
    dlist_destroy(list);
}

void test_hashtable() {
    hashtable* ht;
    int* r;
    int b = 1;
    int choice = 0;
    char key[10];

    srand(time(NULL));
    
    ht = hashtable_create();

    char* keys[] = {"test", "der", "hashtable", "foo", "bar", "hello", "world", "text", "desc", "jo"}; 
        
    for (int i = 0; i < 10; i++) {
        r = malloc(sizeof(int));
        *r = rand() % 200;
        hashtable_set(ht, keys[i], r);    
    }
    
    while (b) {
        printf(CLS);
        printf("\n");
        for (int i = 0; i < ht->size; i++) {        
            if (ht->table[i] != NULL) {                  
                hashtable_entry* iterator = ht->table[i];
                while (iterator != NULL) {
                    printf("%s (hashed to %i) -> %i\n", iterator->key, i, *(int*)iterator->value);
                    iterator = iterator->next;   
                }    
            }   
        }
        printf("\n");
        printf("\n");
        printf("(1)\tInsert an element\n");
        printf("(2)\tRemove an element\n");
        printf("(3)\tGet an element\n");
        printf("(4)\tExit\n");
        printf("\n");

        printf("What would you like to do? ");

        scanf("%d", &choice);

        switch (choice) {
            case 1: // insert
                printf("Enter the key of the element to insert: ");
                fgets(key, 10, stdin);
                r = malloc(sizeof(int));
                *r = rand() % 200;
                hashtable_set(ht, key, r);
                printf("Appended %d.\n", *r);
                break;
            case 2: // remove
                printf("Enter the key of the element to remove: ");
                fgets(key, 10, stdin);
                r = hashtable_remove(ht, key);
                printf("Removed %d.\n", *r);
                break;
            case 3: // get
                printf("Enter the key of the element to get: ");
                fgets(key, 10, stdin);
                printf("you entered %s", key);
                r = hashtable_get(ht, key);
                printf("got %d from key %s.\n", *r, key);
                break;
            default:
                b = 0;
                break;
        }
    }
    hashtable_destroy(ht);
}


