#ifndef HEAP

#define HEAP

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define HEAPSIZE 100

typedef struct {
	int heap[HEAPSIZE];
	int n;
	int mode;
} heap;

void init_heap(heap *h);
void heapify(heap *h, int i);
void build_heap(heap *h);
void swap(int *x, int *y);
void insert_heap(heap *h, int x);
void delete_heap(heap *h, int x);
int search_heap(heap *h, int x);
void print_heap(heap *h);
int peek_heap(heap *h);
int empty_heap(heap *h);

#endif HEAP
