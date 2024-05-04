#include "graph.h"

void insert_node(node **n, int x)
{
	node *p;

	p = malloc(sizeof(node));
	if (p) {
		p->value = x;
		p->next = *n;
		*n = p;
	} else {
		printf("failed to allocate memory\n");
		exit(1);
	}
}

void delete_node(node **n, int x)
{
	node *p;

	if ((*n)->value == x)
		*n = (*n)->next;
	else {
		for (p = *n; p && p->next && p->next->value != x; p = p->next)
			;
		if (p && p->next)
			p->next = p->next->next;
	}
}

void init_graph(graph *g, int v)
{
	int i;
	g->verticies = v;
	for (i = 0; i < v; i++)
		*(g->edges + i) = NULL;
}

void insert_edge(graph *g, int x, int y, int d)
{
	insert_node(&(*(g->edges + x)), y);
	if (!d)
		insert_edge(g, y, x, 1);
}

void delete_edge(graph *g, int x, int y, int d)
{

	delete_node(&(*(g->edges + x)), y);
	if (!d)
		delete_edge(g, y, x, 1);
}

void read_graph(graph *g)
{
	int i, t;
	int e, v;
	int x, y;

	assert(scanf("%d %d", &e, &v));
	init_graph(g, v);
	for (i = 0; i < e; i++) {
		assert(scanf("%d %d", &x, &y));
		insert_edge(g, x, y, 0);
	}
}

void print_graph(graph *g)
{
	int i;
	node *p;

	for (i = 0; i < g->verticies; i++) {
		printf("%d: ", i);
		for (p = *(g->edges + i); p; p = p->next)
			printf("%d -> ", p->value);
		printf("null\n");
	}
}

void init_search(graph *g)
{
	int i;
	vertex *v;

	for (i = 0; i < g->verticies; i++) {
		v = verticies + i;
		v->state = 0;
		v->distance = -1;
		v->predecessor = -1;
	}
}

void bfs(graph *g, int s)
{
	int d, t;
	queue q;
	vertex *v;
	node *p;

	d = 0;
	init_queue(&q);
	enqueue(&q, s);
	v = verticies + s;
	v->state = 1;

	while (!empty_queue(&q)) {
		t = dequeue(&q);
		for (p = *(g->edges + t); p; p = p->next) {
			v = verticies + p->value;
			if (!v->state) {
				v->state = 1;
				v->distance = d;
				v->predecessor = t;
				enqueue(&q, p->value);
			}
		}
		d++;
	}
}

void dfs(graph *g, int s)
{
	int d, t;
	stack st;
	vertex *v;
	node *p;

	d = 0;
	init_stack(&st);
	push(&st, s);
	v = verticies + s;
	v->state = 1;

	while (!empty_stack(&st)) {
		t = pop(&st);
		for (p = *(g->edges + t); p; p = p->next) {
			v = verticies + p->value;
			if (!v->state) {
				v->state = 1;
				v->distance = d;
				v->predecessor = t;
				push(&st, p->value);
			}
		}
		d++;
	}
}

void pp_r(int x, int y)
{
	if (x == y || y == -1)
		printf("%d -> ", x);
	else {
		pp_r(x, (verticies + y)->predecessor);
		printf("%d -> ", y);
	}
}

void print_path(int x, int y)
{
	pp_r(x, y);
	printf("\b\b\b  \n");
}
