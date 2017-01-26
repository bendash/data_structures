/**
 * Implementation file for Binary Tree
 *
 * @author Benjamin Walch
 */

#include "btree.h"

btree_node* btree_create() {
    btree_node* node = malloc(sizeof(btree_node));
    
    node->left = NULL;
    node->right = NULL;
    node->data = NULL;
    
    return node;
}

void btree_destroy(btree_node* tree) {
    if (tree) {
        btree_destroy(tree->left);
        btree_destroy(tree->right);
        free(tree);
    }
}

// helper func
int btree_cmp(void* el1, void* el2) {
    return *((int*)el1) - (*(int*)el2);
}

int btree_is_empty(btree_node* tree) {
    return tree->data == NULL;
}

void btree_insert(btree_node* tree, void* el) {
    if (btree_is_empty(tree)) {
        tree->data = el;
        return;
    }
    btree_node* new_node = btree_create();
    new_node->data = el;
    
    // search for proper place
    while(1) {
        if (btree_cmp(tree->data, el) >= 0) {
            if(tree->left == NULL) {
                tree->left = new_node;
                break;
            }
            tree = tree->left;
        } else {
            if(tree->right == NULL) {
                tree->right = new_node;
                break;
            }
            tree = tree->right;
        }
    }
}

int btree_contains(btree_node* tree, void* el) {
    if (tree == NULL || btree_is_empty(tree)) {
        return 0;
    }
    if (btree_cmp(tree->data, el) == 0) {
        return 1;
    }
    if (tree->left != NULL) {
        if (btree_contains(tree->left, el)) {
            return 1;
        }
    }
    if (tree->right != NULL) {
        if (btree_contains(tree->right, el)) {
            return 1;
        }
    }
    return 0;
}