#include "tree.h"

void print_node(tree *t, int i)
{
	int j;

	if (t) {
		for (j = 0; j < i; j++)
			putchar(' ');
		printf("%d\n", t->item);
		print_node(t->left, i+1);
		print_node(t->right, i+1);
	}
}

void wrapper(tree *t)
{
	int i;

	print_node(t, 0);
	for (i = 0; i < 10; i++)
		putchar('-');
	putchar('\n');
}

tree *concat_minimum(tree *s, tree *t)
{
	int min;
	tree *v;

	v = NULL;
	min = minimum_tree(t)->item;
	t = delete_tree(t, min);
	insert_tree(&v, min);
	v->left = s;
	v->right = t;
	return v;
}

tree *concat_maximum(tree *s, tree *t)
{
	int max;
	tree *v;

	v = NULL;
	max = maximum_tree(s)->item;
	s = delete_tree(s, max);
	insert_tree(&v, max);
	v->left = s;
	v->right = t;
	return v;
}

int main(void)
{
	int i;
	tree *s, *t, *v;

	s = t = v = NULL;
	for (i = 0; i < 10; i++) {
		insert_tree(&s, rand() % 10);
		insert_tree(&t, rand() % 10 + 10);
	}
	wrapper(s);
	wrapper(t);
	v = concat_maximum(s, t);
	wrapper(v);
	v = NULL;
	v = concat_minimum(s, t);
	wrapper(v);
	return 0;
}
