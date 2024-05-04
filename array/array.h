#ifndef ARRAY

#define ARRAY

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
	int capacity;
	int last;
	int *array;
} array;

void init_array(array *a, int c);
int empty_array(array *a);
int head_array(array *a);
void expand(array *a);
void shrink(array *a);
void prepend_array(array *a, int x);
void append_array(array *a, int x);
void insert_array(array *a, int i, int x);
int pop_array(array *a);
int dequeue_array(array *a);
int delete_array(array *a, int i);
int search_array(array *a, int x);
void print_array(array *a);

#endif
