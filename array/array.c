#include "array.h"

void init_array(array *a, int c)
{
	a->capacity = c;
	a->last = -1;
	a->array = malloc(sizeof(int) * c);
}

int empty_array(array *a)
{
	return !(a->last + 1);
}

int head_array(array *a)
{
	if (empty_array(a)) {
		printf("array is empty\n");
		return 0;
	}
	return *(a->array);
}

void expand(array *a)
{
	int *tmp;

	if (a->last + 1 >= a->capacity) {
		a->capacity <<= 1;
		tmp = realloc(a->array, a->capacity);
		assert(tmp);
		a->array = tmp;
	}
}

void shrink(array *a)
{
	int *tmp;

	if (a->last <= (a->capacity >> 2)) {
		a->capacity >>= 1;
		tmp = realloc(a->array, a->capacity);
		assert(tmp);
		a->array = tmp;
	}
}

void prepend_array(array *a, int x)
{
	int i;

	expand(a);
	for (i = a->last++; i >= 0; i--)
		*(a->array + i + 1) = *(a->array + i);
	*(a->array) = x;
}

void append_array(array *a, int x)
{
	expand(a);
	*(a->array + ++(a->last)) = x;
}

void insert_array(array *a, int i, int x)
{
	int j;

	expand(a);
	for (j = a->last++; j >= i; j--)
		*(a->array + j + 1) = *(a->array + j);
	*(a->array + i) = x;
}

int pop_array(array *a)
{
	shrink(a);
	if (empty_array(a)) {
		printf("array is empty\n");
		return 0;
	}
	return *(a->array + a->last--);
}

int dequeue_array(array *a)
{
	int i, x;

	shrink(a);
	if (empty_array(a)) {
		printf("array is empty\n");
		return 0;
	}
	x = *(a->array);
	for (i = 0; i <= a->last; i++)
		*(a->array + i) = *(a->array + i + 1);
	a->last--;
	return x;
}

int delete_array(array *a, int i)
{
	int j, x;

	shrink(a);
	x = *(a->array + i);
	for (j = i; j <= a->last; j++)
		*(a->array + j) = *(a->array + j + 1);
	a->last--;
	return x;
}

int search_array(array *a, int x)
{
	int i;

	for (i = 0; i < a->capacity; i++)
		if (a->array[i] == x)
			return i;
	return -1;
}

void print_array(array *a)
{
	int i;

	for (i = 0; i <= a->last; i++)
		printf("%d ", a->array[i]);
	putchar('\n');
}
