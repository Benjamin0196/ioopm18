#include "hash_table.h"
/* WARNING!
   Only error when using more than 17 buckets when using hash_table_destroy function. --TODO fix! 
*/
#define No_Buckets 17



int main(int argc, char *argv[]){
  ioopm_hash_table_t *hash_table = ioopm_hash_table_create();

  char *string_arr = calloc(1,sizeof("hello"));
  
  string_arr = "hello";
  ioopm_hash_table_insert(hash_table, 9999, string_arr);
  ioopm_hash_table_insert(hash_table, 7777, "Second");
  ioopm_hash_table_insert(hash_table, 8888, "First");
  ioopm_hash_table_insert(hash_table, 6666, "Fourth");
  ioopm_hash_table_insert(hash_table, 12, "Third");
  ioopm_hash_table_insert(hash_table, 34, "Second");

  //ioopm_print_hash_table(hash_table);
  //ioopm_hash_table_clear(hash_table);
  // printf("Hashtable size: %d\n",ioopm_hash_table_size(hash_table));
  ioopm_hash_table_destroy(hash_table);

  printf(":%s\n",string_arr);
  return 0;
}



/* Entry_Create
Param: Integer key, String value, An entry_t next (NULL unless adding several entries)
Returns: Pointer to an entry_t
*/
static entry_t *entry_create(int key, char *value, entry_t *next){

  entry_t *result = calloc(1,sizeof(entry_t));
  result->key   = key;
  result->value = value;
  result->next  = next;

  return result;
}
/* Print Entry 
Prints a single entry_t
Param: Pointer to an entry_t
Returns: VOID
*/
void ioopm_print_entry_t(entry_t *entry){
  int key = entry->key;
  char *value = entry->value;
  printf("Key: %d\nValue: %s\n",key,value);
}


/* Print_hash_table
Prints all nodes in a hash table. 
Param: Pointer to an IOOPM_hash_table_t
Returns: VOID
*/
void ioopm_print_hash_table(ioopm_hash_table_t *ht){
  
  for (int i = 0 ; i < No_Buckets ; i++){
    entry_t *current_entry = ht->buckets[i];
    printf("Bucket: %d\n",i);
    while(current_entry->next != NULL){
      ioopm_print_entry_t(current_entry);
      current_entry = current_entry->next;
    }
    ioopm_print_entry_t(current_entry);
  }
}

/* Hash_table_create
Creates an ioopm hash table and initializes with dummy nodes for all buckets. 
Param: No parameters needed
Returns: Pointer to a hash_table_t
*/
ioopm_hash_table_t *ioopm_hash_table_create(){

  ioopm_hash_table_t *result = calloc(1,sizeof(ioopm_hash_table_t));

  for (int i = 0 ; i < No_Buckets ; i++){
    result->buckets[i] = entry_create(0,NULL,NULL);
  }
  
  return result;
}

/* Find_previous_entry_for_key
Given a key, find_previous, returns the entry_t before the given key. 
Param: Pointer to hash_table_t, int key
Returns: Pointer to an entry_t
*/
static entry_t *find_previous_entry_for_key(ioopm_hash_table_t *ht, int key){  
  int bucket = key % No_Buckets;
  entry_t *return_entry = ht->buckets[bucket];
  entry_t *current_entry = ht->buckets[bucket];

  while(current_entry->key != key){
    return_entry = current_entry;
    current_entry = current_entry->next;
    if(current_entry == NULL){
      return return_entry;
    }
  }
  return return_entry;
}


/* Hash_table_insert
Given a hash_table_t, key and value, the function inserts an entry with the given key value pair in the ht. 
Param: Pointer to a hash_table_t, integer key, string value. 
Returns: VOID
*/
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value){
  /// Calculate the bucket for this entry
  //int bucket = key % No_Buckets;
  /// Search for an existing entry for a key
  entry_t *entry = find_previous_entry_for_key(ht, key);
  entry_t *next = entry->next;

  /// Check if the next entry should be updated or not
  if (next != NULL && next->key == key)
    {
      next->value = value;
    }
  else
    {  
      entry->next = entry_create(key, value, next);
    }
}


char **ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key)
{
  /// Find the previous entry for key
  entry_t *tmp = find_previous_entry_for_key(ht, key);
  entry_t *next = tmp->next;
  if(next != NULL){
    char *value = next->value;
    char **result = &value;

    return result;
  }
  else{
    char *not_valid = NULL;
    char **not_a_valid = &not_valid;
    return not_a_valid;
  }  
}


/*
  WARNING! 
  Only works for middle entries, untested for first and last entry. -- TODO
 */
ioopm_hash_table_t *ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key){
  if (ioopm_hash_table_lookup(ht,key) != NULL){
    entry_t *previous_entry = find_previous_entry_for_key(ht, key);
    entry_t *temp = previous_entry->next;
    previous_entry->next = previous_entry->next->next;
    entry_destroy(temp);
    return ht;
  }
  else {return ht;};
}


void entry_destroy(entry_t *entry){
  free(entry);
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht){
  
  for (int i = 0 ; i < No_Buckets ; i++){
    entry_t *current_entry = ht->buckets[i];
    
    while(current_entry->next != NULL){
      entry_destroy(current_entry);
      current_entry = current_entry->next;
    }
    entry_destroy(current_entry);
    current_entry = ht->buckets[i];
  }

  free(ht);
  puts("Hashtable successfully destroyed!");
}

int ioopm_hash_table_size(ioopm_hash_table_t *ht){
  int result = 0; 
  for (int i = 0 ; i < No_Buckets ; i++){
    entry_t *current_entry = ht->buckets[i];
    result--;
    while(current_entry->next != NULL){
      current_entry = current_entry->next;
      result++;
    }
    result++;
    current_entry = ht->buckets[i];
  }
  return result;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht){
  for (int i = 0 ; i < No_Buckets ; i++){
    if(ht->buckets[i]->next != NULL){
      return false;
    }
  }
  return true;
}

void ioopm_hash_table_clear(ioopm_hash_table_t *ht){
  
  for (int i = 0 ; i < No_Buckets ; i++){
    entry_t *current_entry = ht->buckets[i];
    entry_t *first_entry = ht->buckets[i-1];
    while(current_entry->next != NULL){
      entry_destroy(current_entry);
      current_entry = current_entry->next;
    }
    if( i > 1){
      first_entry = entry_create(0,NULL,NULL);
    }
    current_entry = ht->buckets[i];
    if (first_entry->value != NULL){
    }
  }
 
}




int *ioopm_hash_table_keys(ioopm_hash_table_t *ht){
  
  int ht_size = ioopm_hash_table_size(ht);
  int keysarr[ht_size];
  int *keys = calloc(1,sizeof(keysarr));;
  int key = 0;
  for (int i = 0 ; i < No_Buckets ; i++){
    entry_t *current_entry = ht->buckets[i];
    int value_numb = 0;
    
    while(current_entry->next != NULL){
      if (value_numb != 0){
	keys[key] = current_entry->key;
	key++;
      }
      value_numb++;
      current_entry = current_entry->next;
    }
    
    if(value_numb != 0){
      keys[key] = current_entry->key;
      key++;
      
    }
  }

  return keys;
}

