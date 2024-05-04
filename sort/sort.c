#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define L 1000
#define S 1000

void swap(int *a, int i, int j)
{
	if (*(a + i) != *(a + j)) {
		*(a + i) = *(a + i) ^ *(a + j);
		*(a + j) = *(a + i) ^ *(a + j);
		*(a + i) = *(a + i) ^ *(a + j);
	}
}

void selection(int *a, int s)
{
	int i, j, m;

	for (i = 0; i < s; i++) {
		for (j = m = i; j < s; j++)
			if (*(a + j) < *(a + m))
				m = j;
		swap(a, i, m);
	}
}

void insertion(int *a, int s)
{
	int i, j, key;

	for (i = 1; i < s; i++) {
		key = *(a + i);
		for (j = i - 1; j >= 0 && *(a + j) > key; j--)
			*(a + j + 1) = *(a + j);
		*(a + j + 1) = key;
	}
}

void merge(int *a, int p, int q, int r)
{
	int *b, *c, i, j, k, nl, nr;

	nl = q - p + 1;
	nr = r - q;

	b = malloc(sizeof(int) * (nl + 1));
	assert(b);
	c = malloc(sizeof(int) * (nr + 1));
	assert(c);

	for (i = 0; i < nl; i++)
		*(b + i) = *(a + p + i);
	*(b + i) = INT_MAX;
	for (j = 0; j < nr; j++)
		*(c + j) = *(a + q + 1 + j);
	*(c + j) = INT_MAX;

	i = j = 0;
	for (k = p; k <= r; k++) {
		if (*(b + i) <= *(c + j))
			*(a + k) = *(b + i++);
		else
			*(a + k) = *(c + j++);
	}
	free(b);
	free(c);
}

void mergesort(int *a, int p, int r)
{
	int q;

	if (p >= r)
		return;

	q = (p + r) / 2;
	mergesort(a, p, q);
	mergesort(a, q + 1, r);
	merge(a, p, q, r);
}

int partition(int *a, int p, int r)
{
	int q, u;

	q = p;
	for (u = p; u < r; u++)
		if (*(a + u) <= *(a + r))
			swap(a, u, q++);
	swap(a, q, r);
	return q;
}

void quicksort(int *a, int p, int r)
{
	int q;

	if (p >= r)
		return;

	q = partition(a, p, r);
	quicksort(a, p, q - 1);
	quicksort(a, q + 1, r);
}

int *count_keys_equal(int *a, int m, int n)
{
	int *equal, i;

	equal = malloc(sizeof(int) * m);
	assert(equal);
	for (i = 0; i < m; i++)
		*(equal + i) = 0;
	for (i = 0; i < n; i++)
		(*(equal + *(a + i)))++;
	return equal;
}

int *count_keys_less(int *equal, int m)
{
	int i, *less;

	less = malloc(sizeof(int) * m);
	assert(less);
	*less = 0;
	for (i = 1; i < m; i++)
		*(less + i) = *(less + i - 1) + *(equal + i - 1);
	free(equal);
	return less;
}

int *rearrange(int *a, int *less, int m, int n)
{
	int i, index, key, *b;

	b = malloc(sizeof(int) * n);
	assert(b);
	for (i = 0; i < n; i++) {
		key = *(a + i);
		index = *(less + key);
		*(b + index) = *(a + i);
		(*(less + key))++;
	}
	free(less);
	return b;
}

int *countsort(int *a, int m, int n)
{
	int *equal, *less;

	equal = count_keys_equal(a, m, n);
	less  = count_keys_less (equal, m);
	return rearrange(a, less, m, n);
}

void random_sample(int *a, int s)
{
	int i;

	for (i = 0; i < s; i++)
		*(a + i) = rand() % L;
}

int check_sort(int *a, int s)
{
	int i;

	for (i = 0; i < s - 1; i++)
		if (*(a + i) > *(a + i + 1))
			return 0;
	return 1;
}

void print_array(char *h, int *a, int s)
{
	int i;

	printf("%s\n", h);
	for (i = 0; i < 10; i++) {
		printf("%4d", *(a + i));
	}
	putchar('\n');
	for (i = 0; i < 4 + 1; i++) {
		putchar(' ');
	}
	printf("...\n");
	for (i = s - 10; i < s; i++) {
		printf("%4d", *(a + i));
	}
	putchar('\n');
}

int main(void)
{
	int a[S], *b, i, r;

	r = 0;
	random_sample(a, S);
	print_array("Sample: ", a, S);
	selection(a, S);
	print_array("Selection: ", a, S);
	r |= check_sort(a, S) << 0;
	random_sample(a, S);
	print_array("Sample: ", a, S);
	insertion(a, S);
	print_array("Insertion: ", a, S);
	r |= check_sort(a, S) << 1;
	random_sample(a, S);
	print_array("Sample: ", a, S);
	mergesort(a, 0, S - 1);
	print_array("Mergesort: ", a, S);
	r |= check_sort(a, S) << 2;
	random_sample(a, S);
	print_array("Sample: ", a, S);
	quicksort(a, 0, S - 1);
	print_array("Quicksort: ", a, S);
	r |= check_sort(a, S) << 3;
	random_sample(a, S);
	print_array("Sample: ", a, S);
	b = countsort(a, L, S);
	print_array("Count Sort: ", b, S);
	r |= check_sort(b, S) << 4;
	printf("Selection sort: %s\n",
			(r & 1 << 0) ? "pass" : "fail");
	printf("Insertion sort: %s\n",
			(r & 1 << 1) ? "pass" : "fail");
	printf("Merge sort: %s\n",
			(r & 1 << 2) ? "pass" : "fail");
	printf("Quick sort: %s\n",
			(r & 1 << 3) ? "pass" : "fail");
	printf("Count sort: %s\n",
			(r & 1 << 4) ? "pass" : "fail");
	return 0;
}
