#ifndef TREE

#define TREE

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct tree {
	int item;
	struct tree *left;
	struct tree *right;
} tree;

tree *init_tree(void);
int empty_tree(tree *t);
tree *search_tree(tree *t, int x);
void insert_tree(tree **t, int x);
void print_tree(tree *t);
tree *successor_tree(tree *t);
tree *minimum_tree(tree *t);
tree *maximum_tree(tree *t);
tree *predecessor_tree(tree *t);
tree *delete_tree(tree *t, int x);

#endif
