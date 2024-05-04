#include "btree.h"

int t = 0;
btnode *root = NULL;

btnode *new_node(void) {
	btnode *x;
	int i;

	x = malloc(sizeof(*x));
	assert(x);
	x->leaf = 1;
	x->n = 0;
	for (i = 0; i < MAX; i++) {
		x->key[i] = 0;
		x->link[i] = NULL;
	}
	return x;
}

void free_btree(btnode *x) {
	int i;

	if (!x->leaf) {
		for (i = 0; i < x->n; i++) {
			free_btree(x->link[i]);
		}
	}

	free(x);
}

void init_tree(int x) {
	btnode *r;

	r = new_node();
	root = r;
	t = x;
}

void search_btree(btnode *x, int k, int *i, int *j) {
	*j = 0;
	while (*j < x->n && k > x->key[*j]) {
		(*j)++;
	}
	if (*j < x->n && k == x->key[*j]) {
		return;
	} else if (x->leaf) {
		*i = *j = -1;
		return;
	} else {
		(*i)++;
		search_btree(x->link[*j], k, i, j);
	}
}

void split_child(btnode *x, int i) {
	btnode *y, *z;
	int j;

	y = x->link[i];
	assert(y);
	z = new_node();
	z->leaf = y->leaf;
	z->n = t - 1;
	for (j = 0; j < t - 1; j++) {
		z->key[j] = y->key[j + t];
	}
	if (!y->leaf) {
		for (j = 0; j < t; j++) {
			z->link[j] = y->link[j + t];
		}
	}
	y->n = t - 1;
	for (j = x->n; j >= i + 1; j--) {
		x->link[j + 1] = x->link[j];
	}
	x->link[i + 1] = z;
	for (j = x->n - 1; j >= i; j--) {
		x->key[j + 1] = x->key[j];
	}
	x->key[i] = y->key[t - 1];
	x->n++;
}

void insert_btree(int k) {
	btnode *r, *s;

	r = root;
	if (r->n == 2 * t - 1) {
		s = split_root();
		insert_nonfull(s, k);
	} else {
		insert_nonfull(r, k);
	}
}

btnode *split_root() {
	btnode *s;

	s = new_node();
	s->leaf = 0;
	s->n = 0;
	s->link[0] = root;
	root = s;
	split_child(s, 0);
	return s;
}

void insert_nonfull(btnode *x, int k) {
	int i;

	i = x->n - 1;
	if (x->leaf) {					/* inserting into a leaf */
		while (i >= 0 && k < x->key[i]) {
			x->key[i + 1] = x->key[i];
			i--;
		}
		x->key[i + 1] = k;			/* insert key k in x */
		x->n++;					/* now x has 1 more key */
	} else {
		while (i >= 0 && k < x->key[i]) {	/* find the child where k belongs */
			i--;
		}
		i++;
		if (x->link[i]->n == 2 * t - 1) {	/* split the child if it is full */
			split_child(x, i);
			if (k > x->key[i]) {		/* does k go into x->c[i] or x->c[i+1]? */
				i++;
			}
		}
		insert_nonfull(x->link[i], k);
	}
}

void delete_btree(btnode *x, int k) {
	btnode *l;
	int i, kp, ks;

	i = 0;
	while (i < x->n && k > x->key[i]) {
		i++;
	}
	l = x->link[i];
	if (x->leaf) {
		/* case 1 */
		if (i < x->n && k == x->key[i]) {
			pop_key(x, i);
			x->n--;
		}
		return;
	} else {
		if (i < x->n && k == x->key[i]) {
			/* case 2 */
			if (x->link[i]->n >= t) {
				/* case 2a */
				kp = remove_predecessor(x->link[i]);
				x->key[i] = kp;
				return;
			} else if (x->link[i]->n == t - 1 && x->link[i+1]->n >= t) {
				/* case 2b */
				ks = remove_successor(x->link[i+1]);
				x->key[i] = ks;
				return;
			} else if (x->link[i]->n == x->link[i+1]->n == t - 1) {
				/* case 2c */
				merge_together(x, i);
				delete_btree(l, k);
				return;
			}
		} else {
			/* case 3 */
			if (x->link[i]->n == t - 1) {
				if (i - 1 >= 0 && x->link[i - 1]->n >= t) {
					/* case 3a */
					rotate_right(x, i);
				} else if (i + 1 < t - 1 && x->link[i + 1]->n >= t) {
					/* case 3a */
					rotate_left(x, i);
				} else if (i + 1 < t - 1) {
					/* case 3b */
					merge_together(x, i);
				} else if (i - 1 >= 0) {
					/* case 3b */
					l = x->link[i - 1];
					merge_together(x, i - 1);
				}
			}
			delete_btree(l, k);
		}
	}
}

int pop_key(btnode *x, int i) {
	int j, k;

	k = x->key[i];
	for (j = i; j < x->n; j++) {
		x->key[j] = x->key[j + 1];
	}
	return k;
}

btnode *pop_link(btnode *x, int i) {
	btnode *l;
	int j;

	l = x->link[i];
	for (j = i; j < x->n; j++) {
		x->link[j] = x->link[j + 1];
	}
	return l;
}

void append_key(btnode *x, int k) {
	x->key[x->n] = k;
}

void append_link(btnode *x, btnode *l) {
	x->link[x->n + 1] = l;
}

void insert_key(btnode *x, int i, int k) {
	int j;

	for (j = x->n - 1; j >= i; j--) {
		x->key[j + 1] = x->key[j];
	}
	x->key[j + 1] = k;
}

void insert_link(btnode *x, int i, btnode *l) {
	int j;

	for (j = x->n; j >= i; j--) {
		x->link[j + 1] = x->link[j];
	}
	x->link[j + 1] = l;
}

void rotate_left(btnode *x, int i) {
	int fk, j, k;
	btnode *fl, *p, *s;

	p = x->link[i];
	k = x->key[i];
	s = x->link[i + 1];
	fk = pop_key(s, 0);
	x->key[i] = fk;
	append_key(p, k);
	if (!p->leaf) {
		fl = pop_link(s, 0);
		append_link(p, fl);
	}
	p->n++;
	s->n--;
}

void rotate_right(btnode *x, int i) {
	int lk, j, k;
	btnode *ll, *p, *s;

	p = x->link[i - 1];
	k = x->key[i - 1];
	s = x->link[i];
	lk = pop_key(p, p->n - 1);
	x->key[i - 1] = lk;
	insert_key(s, 0, k);
	if (!s->leaf) {
		ll = pop_link(p, p->n);
		insert_link(s, 0, ll);
	}
	p->n--;
	s->n++;
}

void merge_together(btnode *x, int i) {
	int j, k;
	btnode *p, *s;

	k = x->key[i];
	p = x->link[i];
	s = x->link[i + 1];
	append_key(p, k);
	p->n++;
	for (j = 0; j < s->n; j++) {
		p->key[j + p->n] = s->key[j];
	}
	if (!p->leaf) {
		for (j = 0; j < s->n + 1; j++) {
			p->link[j + p->n] = s->link[j];
		}
	}
	p->n += s->n;
	if (x == root && x->n == 0) {
		root = x->link[0];
		free(x);
	}
}

int remove_predecessor(btnode *x) {
	int p;

	if (x->leaf) {
		p = pop_key(x, x->n - 1);
		x->n--;
		return p;
	} else {
		return remove_predecessor(x->link[x->n]);
	}
}

int remove_successor(btnode *x) {
	int i, p;

	if (x->leaf) {
		p = pop_key(x, 0);
		x->n--;
		return p;
	} else {
		return remove_successor(x->link[0]);
	}
}

const int k = 2;

void print_btree(btnode *x, int id) {
	int i, j;

	for (i = 0; i < id * k; i++) {
		putchar(' ');
	}
	for (i = 0; i < x->n; i++) {
		printf("%*d", k, x->key[i]);
		for (j = 0; j < k; j++) {
			putchar(' ');
		}
	}
	putchar('\n');
	if (!x->leaf) {
		for (i = 0; i < (x->n + 1); i++) {
			print_btree(x->link[i], id + 1);
		}
	}
}
