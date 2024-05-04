#include "list.h"

list *init_list(void)
{
	return NULL;
}

int empty_list(list *l)
{
	return l == NULL;
}

list *search_list(list *l, int x)
{
	if (l == NULL)
		return NULL;
	else if (l->item == x)
		return l;
	else
		return search_list(l->next, x);
}

list *predecessor_list(list *l, int x)
{
	if (l == NULL || l->next == NULL)
		return NULL;
	else if ((l->next)->item == x)
		return l;
	else
		return predecessor_list(l->next, x);
}

void insert_list(list **l, int x)
{
	list *p;

	p = malloc(sizeof(list));
	assert(p);
	p->item = x;
	p->next = *l;
	*l = p;
}

void delete_list(list **l, int x)
{
	list *n, *p;

	n = search_list(*l, x);
	if (n != NULL) {
		p = predecessor_list(*l, x);
		if (p == NULL)
			*l = n->next;
		else
			p->next = n->next;
		free(n);
	} else
		printf("failed to delete: item not found\n");
}

void print_list(list *l)
{
	while (l != NULL) {
		printf("%d ", l->item);
		l = l->next;
	}
	putchar('\n');
}
