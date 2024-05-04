#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node {
	char *s;
	struct node *left;
	struct node *right;
} node;

node *insert_recursive(node *h, node *n)
{
	if (!h)
		return n;
	else if (strcmp(h->s, n->s) > 0)
		h->left = insert_recursive(h->left, n);
	else if (strcmp(h->s, n->s) < 0)
		h->right = insert_recursive(h->right, n);
	return h;
}

void insert(node **h, char *s)
{
	node *n, *p;

	n = malloc(sizeof(node));
	assert(n);
	n->s = malloc(strlen(s) + 1);
	assert(n->s);
	strcpy(n->s, s);
	n->left = n->right = NULL;

	*h = insert_recursive(*h, n);
}

void print_node(node *n)
{
	if (n) {
		print_node(n->left);
		printf("%s\n", n->s);
		print_node(n->right);
	}
}

void free_tree(node *n)
{
	if (n) {
		free_tree(n->left);
		free_tree(n->right);
		free(n->s);
		free(n);
	}
}

void read_file(FILE *f)
{
	char s[100];
	node *h;

	h = NULL;
	while (fscanf(f, "%s", s) > 0) {
		insert(&h, s);
	}
	print_node(h);
	free_tree(h);
	fclose(f);
}

int main(int argc, char *argv[])
{
	FILE *f;

	if (!--argc)
		read_file(stdin);
	else 
		while (argc--) {
			if ((f = fopen(*++argv, "r")) == NULL) {
				printf("failed to open %s\n", *argv);
				exit(1);
			}
			read_file(f);
		}
	return 0;
}
