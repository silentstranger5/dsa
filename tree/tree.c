#include "tree.h"

tree *init_tree(void)
{
	return NULL;
}

int empty_tree(tree *t)
{
	return t == NULL;
}

tree *search_tree(tree *t, int x)
{
	if (t == NULL || x == t->item)
		return t;
	else if (x <  t->item)
		return search_tree(t->left, x);
	else
		return search_tree(t->right, x);
}

void insert_tree(tree **t, int n)
{
	tree *p;

	if (*t == NULL) {
		p = malloc(sizeof(*p));
		assert(p);
		p->item = n;
		p->left = p->right = NULL;
		*t = p;
	} else if ((*t)->item < n) {
		insert_tree(&((*t)->right), n);
	} else {
		insert_tree(&((*t)->left), n);
	}
}

void print_tree(tree *t)
{
	if (t != NULL) {
		print_tree(t->left);
		printf("%d ", t->item);
		print_tree(t->right);
	}
}

tree *successor_tree(tree *t)
{
	tree *s;

	if (t->right == NULL)
		return NULL;
	s = t->right;
	while (s->left != NULL)
		s = s->left;
	return s;
}

tree *minimum_tree(tree *t)
{
	tree *m;

	if (t == NULL)
		return NULL;
	m = t;
	while (m->left != NULL)
		m = m->left;
	return m;
}

tree *maximum_tree(tree *t)
{
	tree *m;

	if (t == NULL)
		return NULL;
	m = t;
	while (m->right != NULL)
		m = m->right;
	return m;
}

tree *predecessor_tree(tree *t)
{
	tree *p;

	if (t->left == NULL)
		return NULL;
	p = t->left;
	while (p->right != NULL)
		p = p->right;
	return p;
}

tree *delete_tree(tree *t, int x)
{
	tree *p;

	if (t == NULL)
		return NULL;
	if (x < t->item)
		t->left = delete_tree(t->left, x);
	else if (x > t->item)
		t->right = delete_tree(t->right, x);
	else {
		if (!t->left) {
			p = t->right;
			free(t);
			return p;
		} else if (!t->right) {
			p = t->left;
			free(t);
			return p;
		} else {
			p = successor_tree(t);
			t->item = p->item;
			t->right = delete_tree(t->right, t->item);
		}
	}
	return t;
}
