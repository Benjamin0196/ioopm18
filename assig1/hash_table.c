#include "hash_table.h"
/* WARNING!
   Only error when using more than 17 buckets when using hash_table_destroy function. --TODO fix! 
*/
#define No_Buckets 17

int main(int argc, char *argv[]){
  ioopm_hash_table_t *hash_table = ioopm_hash_table_create();
  //  hash_table->buckets[0] = entry_create(1,"one",(entry_create(2,"two",(entry_create(3,"three",NULL)))));
  //hash_table->buckets[1] = entry_create(4,"one",(entry_create(5,"two",(entry_create(6,"three",NULL)))));
  //hash_table->buckets[3] = entry_create(7,"one",(entry_create(8,"two",(entry_create(9,"three",NULL)))));

  
  printf("Size of hashtable: %d\n",ioopm_hash_table_size(hash_table));
  ioopm_hash_table_insert(hash_table,0,"FIRSTINSERT");
  ioopm_hash_table_insert(hash_table,112,"SECONDINSERT");
  ioopm_hash_table_insert(hash_table,3125,"TURDINSERT");

  printf("Size of hashtable: %d\n",ioopm_hash_table_size(hash_table));
  //  ioopm_print_hash_table(hash_table);
  


  
  //char **value_return = ioopm_hash_table_lookup(hash_table,127);
  
  //  printf("RESULT WAS: %s\n", *value_return);

  //puts("OG Hash:");
  
  //ioopm_print_hash_table(hash_table);

  
  //puts("New Hash:");

  //ioopm_hash_table_destroy(hash_table); 
  //ioopm_print_hash_table(hash_table);

  //    ioopm_print_entry_t(find_previous_entry_for_key(hash_table,129));
  return 0;
}

static entry_t *entry_create(int key, char *value, entry_t *next){

  entry_t *result = calloc(1,sizeof(entry_t));
  result->key   = key;
  result->value = value;
  result->next  = next;

  return result;
}

void ioopm_print_entry_t(entry_t *entry){
  int key = entry->key;
  char *value = entry->value;
  printf("Key: %d\nValue: %s\n",key,value);
}


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


ioopm_hash_table_t *ioopm_hash_table_create(){

  ioopm_hash_table_t *result = calloc(1,sizeof(ioopm_hash_table_t));

  for (int i = 0 ; i < No_Buckets ; i++){
    result->buckets[i] = entry_create(0,NULL,NULL);
  }
  
  return result;
}

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
