#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include "tree.h"

typedef struct node node_t;

struct tree 
{
  node_t *root; 
};

struct node
{
  int key;
  void *value;
  node_t *left;
  node_t *right;
};

enum node_type { LEAF = 0, LEFT_ONLY, RIGHT_ONLY, LEFT_RIGHT };

/// Internal node operations

static node_t *node_create(int key, void *value)
{
  node_t *n = calloc(1, sizeof(node_t));
  n->key = key;
  n->value = value;
  return n;
}

static enum node_type node_type(node_t *n)
{
  if (n->left && n->right) return LEFT_RIGHT;
  if (n->left) return LEFT_ONLY;
  if (n->right) return RIGHT_ONLY;
  return LEAF;
}

static void node_delete_deep(node_t *n)
{
  if (n)
    {
      node_delete_deep(n->left);
      node_delete_deep(n->right);
      free(n);
    }
}

/// Find operations

static node_t **find_largest(node_t **n)
{
  while ((*n)->right)
    {
      n = &(*n)->right;
    }

  return n;
}

static node_t **find_node_in_parent(node_t **n, int key)
{
  while (true)
    {
      if ((*n) == NULL) return n;
      if ((*n)->key == key) return n;

      if ((*n)->key < key)
        {
          n = &(*n)->right;
        }
      else
        {
          n = &(*n)->left;
        }
      
    }

  assert(false); /// Should never happen!
  return NULL;
}

/// Tree operations

tree_t *ioopm_tree_create(void) 
{
  return calloc(1, sizeof(tree_t));
}

void ioopm_tree_destroy(tree_t *t) 
{
  node_delete_deep(t->root);
  free(t);
}

void *ioopm_tree_insert(tree_t *t, int key, void *value) 
{
  assert(value != NULL);
  
  node_t **n = find_node_in_parent(&t->root, key);

  if (*n != NULL)
    {
      /// Update existing node
      void *old_value = (*n)->value;
      (*n)->value = value;
      return old_value;
    }
  else
    {
      *n = node_create(key, value);      
      return NULL;
    }
}

void *ioopm_tree_remove(tree_t *t, int key)
{
  node_t **n = find_node_in_parent(&(t->root), key);

  void *value = (*n)->value;
  node_t *node_to_remove = *n;

  switch (node_type(*n))
    {
    case LEAF:
      *n = NULL; break;
    case LEFT_ONLY:
      *n = node_to_remove->left; break;
    case RIGHT_ONLY:
      *n = node_to_remove->right; break;
    case LEFT_RIGHT:
      {
        node_t **r = find_largest(&(node_to_remove->left));
        (*n)->key = (*r)->key;
        (*n)->value = (*r)->value;
        node_to_remove = *r;
        *r = NULL;
        break;
      }
    default: assert(false);
    }

  free(node_to_remove);
  return value;
}

void *ioopm_tree_get(tree_t *t, int key) 
{
  node_t *n = *find_node_in_parent(&t->root, key);

  if (n)
    {
      return n->value;
    }
  else
    {
      return NULL;
    }
}

bool ioopm_tree_contains_key(tree_t *t, int key) 
{
  node_t *n = *find_node_in_parent(&t->root, key);
  return n != NULL;
}

static void node_dump(node_t *n, int depth)
{
  if (n)
    {
      node_dump(n->right, depth + 1);
      for (int i = 0; i < depth; ++i) printf("\t");
      printf("key: %d\n", n->key);
      node_dump(n->left, depth + 1);
    }
}

void tree_dump(tree_t *t)
{
  puts("Tree:");
  node_dump(t->root, 0);
  puts("----");
}

int main(int argc, char *argv[])
{
  tree_t *t = ioopm_tree_create();
  ioopm_tree_insert(t, 3, "Three");
  ioopm_tree_insert(t, 5, "Five");
  ioopm_tree_insert(t, 4, "Four");
  ioopm_tree_insert(t, 6, "Six");
  ioopm_tree_insert(t, 2, "Two");
  tree_dump(t);
  ioopm_tree_remove(t, 5);
  tree_dump(t);
  ioopm_tree_remove(t, 3);
  tree_dump(t);
  ioopm_tree_destroy(t);
  return 0;
}

