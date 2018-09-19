#pragma once

#include <stdbool.h>

typedef struct tree tree_t;

/// Create a new empty tree 
tree_t *ioopm_tree_create(void);

/// Remove a tree, freeing all its memory -- but not the values
void ioopm_tree_destroy(tree_t *t);

/// Insert a (key, value) into a tree t
void *ioopm_tree_insert(tree_t *t, int key, void *value);

/// Remove a key and its associated value from a tree t
void *ioopm_tree_remove(tree_t *t, int key);

/// Lookup the value for a key in a tree t
void *ioopm_tree_get(tree_t *t, int key);

/// Check if key is mapped in a tree t
bool ioopm_tree_contains_key(tree_t *t, int key);


