#ifndef BTREE

#define BTREE

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX 32

typedef struct btnode {
	int n;
	int leaf;
	int key[MAX];
	struct btnode *link[MAX+1];
} btnode;

extern int t;
extern btnode *root;

btnode *new_node(void);
void init_tree(int x);
void free_btree(btnode *x);

void search_btree(btnode *x, int k, int *i, int *j);

void insert_btree(int k);
void split_child(btnode *x, int i);
btnode *split_root();
void insert_nonfull(btnode *x, int k);

void delete_btree(btnode *x, int k);
int pop_key(btnode *x, int i);
btnode *pop_link(btnode *x, int i);
void append_key(btnode *x, int k);
void append_link(btnode *x, btnode *l);
void insert_key(btnode *x, int i, int k);
void insert_link(btnode *x, int i, btnode *l);
void rotate_left(btnode *x, int i);
void rotate_right(btnode *x, int i);
void merge_together(btnode *x, int i);
int remove_predecessor(btnode *x);
int remove_successor(btnode *x);

void print_btree(btnode *x, int id);

#endif
