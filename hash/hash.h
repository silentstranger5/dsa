#ifndef HASH

#define HASH

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 100
#define STRSIZE  100

typedef struct node {
	char *k, *v;
	struct node *next;
} node;

extern int  nkeys;
extern node *table[HASHSIZE];
extern char *keys [HASHSIZE];

int hash(char *s);
node *get_node(char *s, char *t);
void put_hash(char *s, char *t);
node *delete_recursive(char *s, node *p);
void delete_hash(char *s);
node *get_hash(char *s);
void list_keys(void);

#endif
