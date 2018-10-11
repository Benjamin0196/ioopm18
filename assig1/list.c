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
  char *shelf;
  link_t *next;
};

struct list
{
  link_t *first;
  link_t *last;
};

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
  createdlink->shelf = NULL;

  return createdlink;
  
}

char *list_getshelfname(list_ *list, int index)
{
  int i = 0;
  char *str = " ";
  struct lik *travlist;
  
  travlist = list->first;
  for(;(i < index && travlist->next != 0); i++)
    {
      travlist = travlist->next;
    }
  str = travlist->shelf;
  return str;
}


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

bool list_remove(list_t *list, int index, int *elem)
{
  struct link *travlist;

  if(list->first != 0)
    {
      travlist = list->first;
      for(int i = 0; (i = index || trvlist->next == 0); i++)
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

int list_length(list_t *list)
{
  int i =0;
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
      return sum
    }
  return 0;
}

int *list_first(list_1 *list)
{
  return(list_get(list, 0));
}

void clear(void){
  int i;
  do{
    u = getchar();
  }
  while(u != '\n');
}

int main()
{
  list_t *list = list_new();

  int ind;
  int val;
  char c;

  while(true){
    int len = list_length(list);
    printf("Längden av listan; %d\n", len);
    puts(" [a]dd index value\n app[e]nd value\n [p]repend value\n [g]et index value\n [f]irst element in list\n [l]ast element");

    scanf("%c", &c);
    switch(c){

    case 'a':
      clear();

      scanf("%d %d", &ind, &val);
      printf("index: %d\nvalue: %\n",ind,val);

      list_insert(list, ind, val);
      clear();
      break;

    case 'g':
      clear();
      puts("vilket index vill du visa value i:");
      scanf("&d", &ind);

      if (len < ind || len == 0) printf("det finns inget elemt vid index %d\n", ind);
    }
    clear();
    break;

  case 'f':
    clear();
    if (len == 0) puts("listan e tom, det finns inget first element");
    else{
      int *first = list_first(list);
      printf("första elementet i listan ar: %d\n", *first);
    }
    break;

  case 'l':
    clear();
    if(len == 0) puts("listan e tom, det finns inget last element");
    else{
      int *last = list_last(list);
      printf("sista elementet i listan e: %d\n", *last);
    }
    break;

  case 'e':
    clear();
    puts("vilket value vill du appenda:");
    scanf("%d", &ind);

    list_append(list, ind);
    int *last = list_last(list);
    printf("sista elementet i listan är nu: %d\n", *last)

      clear();
    break;

  case 'p':
    clear();
    puts("vilket value vill du appenda:");
    scanf("%d", & ind);

    list_prepend(list, ind);
    int *first = list_first(list);
    printf("första elementet i listan är nu: %d\n", *first);
    clear();
    break;
  }
  return 0;
}

