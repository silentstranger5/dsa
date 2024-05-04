#include <stdio.h>
#include <stdlib.h>

#define N 4
#define L 100

void fill_random(int n, int (*m)[N])
{
	int i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			*(*(m + i) + j) = rand() % L;
}

void fill_zero(int n, int (*m)[N])
{
	int i, j;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			*(*(m + i) + j) = 0;
}

void multiply_matrix(int n, int (*a)[N], int (*b)[N], int (*c)[N])
{
	int i, j, k;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			for (k = 0; k < n; k++)
				*(*(c + i) + j) += (*(*(a + i) + k) * *(*(b + k) + j));
}

void print_matrix(int n, int (*m)[N])
{
	int i, j;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++)
			printf("%d\t", *(*(m + i) + j));
		putchar('\n');
	}
	putchar('\n');
}

int main(void)
{
	int a[N][N];
	int b[N][N];
	int c[N][N];

	fill_random(N, a);
	fill_random(N, b);
	fill_zero(N, c);
	multiply_matrix(N, a, b, c);
	print_matrix(N, a);
	print_matrix(N, b);
	print_matrix(N, c);
	return 0;
}
