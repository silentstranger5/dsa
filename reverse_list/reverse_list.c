#include "list.h"

void reverse_list(list **h)
{
	list *p, *c, *n;

	if (!h || !*h)
		return;

	c = *h;
	p = n = NULL;
	while (c) {
		n = c->next;
		c->next = p;
		p = c;
		c = n;
	}
	*h = p;
}

list *reverse_list_recursive(list *p, list *c, list *n)
{
	c->next = p;
	if (!n)
		return c;
	else
		return reverse_list_recursive(c, n, n->next);
}

int main(void)
{
	int i;
	list *h;

	h = NULL;
	for (i = 0; i < 10; i++)
		insert_list(&h, i + 1);
	print_list(h);
	h = reverse_list_recursive(NULL, h, h->next);
	print_list(h);
	return 0;
}
