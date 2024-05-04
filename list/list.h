#ifndef LIST

#define LIST

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct list {
	int item;
	struct list *next;
} list;

list *init_list(void);
int empty_list(list *l);
list *search_list(list *l, int x);
list *predecessor_list(list *l, int x);
void insert_list(list **l, int x);
void delete_list(list **l, int x);
void print_list(list *l);

#endif
