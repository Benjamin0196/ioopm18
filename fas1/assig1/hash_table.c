#include <stdlib.h>
#include <stdio.h>

/// the types from above
typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;
ioopm_hash_table_t *ioopm_hash_table_create();

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


int main(int argc, char *argv[])
{

  return 0;
}

ioopm_hash_table_t *ioopm_hash_table_create(){
  ioopm_hash_table_t *result = calloc(1,sizeof(ioopm_hash_table_t));

  return result;
}

entry_t find_entry_for_key(ioopm_hash_table_t*,int,char*);

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  /// Calculate the bucket for this entry
  int bucket = key % 17;
  /// Search for an existing entry for a key
  entry_t *existing_entry = find_entry_for_key(ht->buckets[bucket], key);

  if (existing_entry != NULL) /// i.e., it exists
    {
      existing_entry->value = value;
    }
  else
    {
      /// Get a pointer to the first entry in the bucket
      entry_t *first_entry = ht->buckets[bucket];
      /// Create a new entry
      entry_t *new_entry = entry_create(key, value, first_entry);
      /// Make the new entry the first entry in the bucket
      ht->buckets[bucket] = new_entry;
    }
}
