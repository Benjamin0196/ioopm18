#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct list list_t;
typedef struct link link_t;

struct link
{
  int value;
  link_t *next;
};

struct list
{
  link_t *first;
  link_t *last;
};

//skapar en ny lista
// retunerar en tom lista

list_t *list_new()
{
list_t *createdlist = malloc(sizeof(list_t));
createdlist ->first = NULL;
createdlist ->last = NULL;
return createdlist;
}

link_t *link_new()
{
  link_t *createdlink = malloc(sizeof(link_t));
  createdlink->value = NULL;
  createdlink->next = NULL;

  return createdlink;
  
}
/// Lägger till ett nytt element i slutet av list
/// \parameter list pointer to list
/// \parameter element där integer blir appended

void list_append(list_t *list, int elem)
{
  link_t *new_l = link_new();
  new_l->value = elem;

  if (list->last == 0){

    list->last = new_l;
    list->first= new_l;
  }
  else{
    list->last->next = new_l;
  }

  
}
/// Lägger till ett nytt element i början av listan
/// \parameter list ponter to listan
/// \parameter elem där integer blir prepended
void list_prepend(list_t *list, int elem)
{

  link_t *new_l = link_new();
  new_l->value = elem;

  if(list->last == 0){
    list->last = new_l;
    list->first= new_l;
  }
  else{
    new_l->next = list->first;
    list->first = new_l;
  }
}
/*
Lägger till ett nytt element till givet index. 
Valida indexes är [0..size]. 
Ex:
/// list_t *l = list_new(); // l == []
/// list_insert(l, 0, 42);  // l == [42]
/// list_insert(l, 0, 43);  // l == [43, 42]
/// list_insert(l, 1, 44);  // l == [43, 44, 42]
/// list_insert(l, 5, 45);  // l == [43, 44, 42]

The last case fails (och returnerar false)
på grund av size är 3, villket betyder att 5 är inte ett valid index. 
Notera att insert at index 0 betyder det samma som prepend 
och att insert index size är det samma som append. 

Negativa indexes ska fungera:

/// list_insert(l, -1, 45);       // l == [43, 44, 42, 45]

ett possitivt index ska kunn bli beräknade från a.
negativa index ska fungera på detta sätt : pos_i = size + 1 + neg_i. 
parameter list pointer till list
parameter index, indexet för elem till att bli inserted i
parameter elem  där integer kommer att bli prepended
returnerar true if succeeded, else false
*/

bool list_insert(list_t *list, int index, int elem)
{
  struct link *travlist;
  struct link *travlist_prev = 0;

  if(list->first == 0){
    if (index !=0){
      puts("ej tillåtet index");
      return false;
    }
    link_t *new = link_new();
    new->value = elem;
    list->first = new;
    list->last = new;
    return true;
  }

  travlist = list->first;

  for(int i = 0; i < index; i++){
    if (travlist->next == 0) {
      puts("dåligt index");
      return false;
    }
    travlist_prev = travlist;
    travlist = travlist->next;
  }

  link_t *new = link_new();
  new->value = elem;
  new->next = travlist;

  if (travlist_prev != 0) travlist_prev->next = new;

  if(index == 0)
    {
      list->first = new;
    }
  return true;
}
/*
Tarbort ett element från en list.
Ex: (assume l == [43, 44, 42, 45])

///int elem;
///list_remove(l, 1, &elem);  // l = [43, 42, 45], elem == 44
/// list_remove(l, -1, &elem); // l = [43, 42], elem == 45

parameter list  pointer till list
parameter index the index till att ta bort
parameter elem en pekare to vart elementet kan lagras
returns true if succeeded, else 
*/
bool list_remove(list_t *list, int index, int *elem)
{
  struct link *travlist;

  if(list->first != 0)
    {
      travlist = list->first;
      for(int i = 0; (i = index || travlist->next == 0); i++)
        {
          travlist = travlist->next;
        }
      if (travlist == 0) return false;
      else
        {
          elem = &travlist->value;
          return true;
        }
    }
  return false;
}
/*
Returnerar element i givet index
parameter list  pointer till list
parameter index, index som ska returneras
returnerar en pointer till element i index index
*/
int *list_get(list_t *list, int index)
{
  int i = 0;
  int *value = 0;
  struct link *travlist;

  travlist = list->first;
  for(;(i < index && travlist->next != 0); i++)
    {
      travlist = travlist->next;
    }
  value = &travlist->value;
  return value;
}
/*
Returnerar längden av en list. Den är odefinerad
när list_length beräknar O(n) gånger eller
när det är en size counter i the list object
som är manipulerad av insert, remove, etc. 
parameter list the list
returnerar listans längd
*/
int list_length(list_t *list)
{
  int i = 0;
  struct link *travlist;
  if (list->first != 0)
    {
      travlist = list->first;
      for(i = 1; travlist->next != 0; i++)
        {
          travlist = travlist->next;
        }
      return i;
    }
  return 0;
}

int list_sum(list_t *list)
{
  int i = 0;
  int sum = 0;
  struct link *travlist;
  if (list->first != 0)
    {
      travlist = list->first;
      for(i = 1; travlist->next != 0; i++)
        {
          sum = sum + travlist->value;
          travlist = travlist->next;
        }
      return sum;
    }
  return 0;
}

int *list_first(list_t *list)
{
  return(list_get(list, 0));
}

void clear(void){
  int u;
  do{
    u = getchar();
  }
  while(u != '\n');
}
/*
TODO

ioopm_list_t *ioopm_linked_list_create()                                                  [x]

void ioopm_linked_list_destroy(ioopm_list_t *list);                                       [x]

void ioopm_linked_list_append(ioopm_list_t *list, int value);                             [x]

void ioopm_linked_list_prepend(ioopm_list_t *list, int value);                            [x]

void ioopm_linked_list_insert(ioopm_list_t *list, int index, int value);                  [x]

int ioopm_linked_list_remove(ioopm_list_t *list, int index);                              [x]

int ioopm_linked_list_get(ioopm_list_t *list, int index);                                 [x]

bool ioopm_linked_list_contains(ioopm_list_t *list, int element);                         []

int ioopm_linked_list_size(ioopm_list_t *list);                                           [x]

bool ioopm_linked_list_is_empty(ioopm_list_t *list);                                      [x]

void ioopm_linked_list_clear(ioopm_list_t *list);                                         []

bool ioopm_linked_list_all(ioopm_list_t *list, bool (*prop)(int, void *), void *x);       []

bool ioopm_linked_list_any(ioopm_list_t *list, bool (*prop)(int, void *), void *x);       []

void ioopm_linked_apply_to_all(ioopm_list_t *list, void (*fun)(int *, void *), void *x);  []

Har haft problem med min dator och har försökt fixa den. Kommer att skriva in komentarer om hur pogrammet fungerar.
Såg ditt meddelande nu och kunnde inte svara då jag glömmde att ladda mobilen.
Vi har dock bara 5 delar kvar och lösa problemet med min dator, ber om ursäkt över det sena meddelandet.
 */

