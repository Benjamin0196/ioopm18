#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

/// the types from above
typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;
typedef struct option option_t;

ioopm_hash_table_t *ioopm_hash_table_create();
void ioopm_print_hash_table(ioopm_hash_table_t*);
void ioopm_print_entry_t(entry_t*);
void ioopm_hash_table_insert(ioopm_hash_table_t*,int,char*);
static entry_t *find_previous_entry_for_key(ioopm_hash_table_t*,int);
static entry_t *entry_create(int,char*,entry_t*);
char **ioopm_hash_table_lookup(ioopm_hash_table_t*,int);
ioopm_hash_table_t *ioopm_hash_table_remove(ioopm_hash_table_t*, int);
void entry_destroy(entry_t*);
void ioopm_hash_table_destroy(ioopm_hash_table_t*);
int ioopm_hash_table_size(ioopm_hash_table_t*);
bool ioopm_hash_table_is_empty(ioopm_hash_table_t*);
void ioopm_hash_table_clear(ioopm_hash_table_t*);
int *ioopm_hash_table_keys(ioopm_hash_table_t*);
char **ioopm_hash_table_values(ioopm_hash_table_t*);
struct option{
  bool defined;
  char *value;
};

struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t *buckets[17];
};






#endif
