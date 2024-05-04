#include "hash.h"

int  nkeys;
node *table[HASHSIZE];
char *keys [HASHSIZE];

int hash(char *s)
{
	int h;

	h = 0;
	while (*s) {
		h = h + *s;
		s++;
	}
	h %= HASHSIZE;
	return h;
}

node *get_node(char *s, char *t)
{
	node *n;

	n = malloc(sizeof(node));
	assert(n);
	n->k = malloc(STRSIZE);
	assert(n->k);
	strcpy(n->k, s);
	n->v = malloc(STRSIZE);
	assert(n->v);
	strcpy(n->v, t);
	n->next = NULL;
	return n;
}

void put_hash(char *s, char *t)
{
	int i;
	char *u;
	node *n, *pn, *pt;

	i = hash(s);
	n = get_node(s, t);
	u = malloc(STRSIZE);
	assert(u);
	strcpy(u, s);
	if (!*(table + i)) {
		*(table + i) = n;
		*(keys + nkeys++) = u;
		return;
	}
	if (!strcmp(s, (pn = *(table + i))->k)) {
		n->next = pn->next;
		*(table + i) = n;
		free(pn->k);
		free(pn->v);
		free(pn);
		return;
	}
	for (pn = *(table + i); (pt = pn->next); pn = pn->next) {
		if (!strcmp(s, pt->k)) {
			n->next = pt->next;
			pn->next = n;
			free(pt->k);
			free(pt->v);
			free(pt);
			return;
		}
	}
	pn->next = n;
	*(keys + nkeys++) = u;
}

node *delete_recursive(char *s, node *p)
{
	node *n;

	if (!(p && p->next))
		return NULL;
	else if (!strcmp(s, p->k)) {
		n = p->next;
		free(p->k);
		free(p->v);
		free(p);
		return n;
	} else {
		p->next = delete_recursive(s, p->next);
		return p;
	}
}

void delete_hash(char *s)
{
	int i;

	*(table + hash(s)) = delete_recursive(s, *(table + hash(s)));
	for (i = 0; i < nkeys; i++) {
		if (!strcmp(s, *(keys + i))) {
			free(*(keys + i));
			break;
		}
	}
	nkeys--;
	for ( ; i < nkeys; i++) {
		*(keys + i) = *(keys + i + 1);
	}
}

node *get_hash(char *s)
{
	node *n;

	for (n = *(table + hash(s)); n && strcmp(s, n->k); n = n->next)
		;
	return n;
}

void list_keys(void) {
	int i;
	node *n;

	for (i = 0; i < nkeys; i++) {
		n = get_hash(*(keys + i));
		printf("%s: %s\n", n->k, n->v);
	}
}
