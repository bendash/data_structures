/**
 * Header File for Binary Tree
 *
 * @author Benjamin Walch
 */

#ifndef BTREE_H
#define BTREE_H

#include <stdlib.h>

typedef struct BinaryTreeNode btree_node;
struct BinaryTreeNode {
    btree_node* left;
    btree_node* right;
    void* data;
};

/* create a new btree */
btree_node* btree_create();

/* destroys btree */
void btree_destroy(btree_node* tree);

/* checks if tree is empty */
int btree_is_empty(btree_node* tree);

/* insert a new element */
void btree_insert(btree_node* tree, void* el);

/* checks if the tree does contain an element */
int btree_contains(btree_node* tree, void* el);

#endif