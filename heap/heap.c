#include "heap.h"

void init_heap(heap *h)
{
	h->n = 0;
	h->mode = 0;
}

void heapify(heap *h, int i)
{
	int left, right, prior;
	void swap(int *, int *);

	left = 2 * i + 1;
	right = 2 * i + 2;
	prior = i;

	if (h->mode) {
		if (left < h->n && h->heap[left] > h->heap[prior])
			prior = left;
		if (right < h->n && h->heap[right] > h->heap[prior])
			prior = right;
	} else {
		if (left < h->n && h->heap[left] < h->heap[prior])
			prior = left;
		if (right < h->n && h->heap[right] < h->heap[prior])
			prior = right;
	}
	if (i != prior) {
		swap(h->heap + i, h->heap + prior);
		heapify(h, prior);
	}
}

void build_heap(heap *h)
{
	int i;

	for (i = (h->n / 2) - 1; i >= 0; i--)
		heapify(h, i);
}

void swap(int *x, int *y)
{
	*y = *x ^ *y;
	*x = *x ^ *y;
	*y = *x ^ *y;
}

void insert_heap(heap *h, int x)
{
	if (h->n >= HEAPSIZE) {
		printf("failed to insert: heap is full\n");
		return;
	}
	h->heap[h->n++] = x;
	if (h->n > 1)
		build_heap(h);
}

void delete_heap(heap *h, int x)
{
	void swap(int *, int *);
	int  search_heap(heap *, int);
	int  n;

	if (!h->n)
		printf("failed to delete: heap is empty\n");
	else if ((n = search_heap(h, x)) < 0)
		printf("failed to delete: node not found\n");
	else {
		swap(h->heap + n, h->heap + (h->n - 1));
		h->n--;
		build_heap(h);
	}
}

int search_heap(heap *h, int x)
{
	int i;

	for (i = 0; i < h->n; i++)
		if (h->heap[i] == x)
			return i;
	return -1;
}

void print_heap(heap *h)
{
	int i;

	for (i = 0; i < h->n; i++)
		printf("%d ", h->heap[i]);
	putchar('\n');
}

int peek_heap(heap *h)
{
	if (h->n > 0)
		return *(h->heap);
	else
		return 0;
}

int empty_heap(heap *h)
{
	return !h->n;
}
