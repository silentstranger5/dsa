#ifndef GRAPH

#define GRAPH

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"
#include "stack.h"

#define MAXG 100

typedef struct node {
	int value;
	struct node *next;
} node;

typedef struct {
	node *edges[MAXG];
	int verticies;
} graph;

typedef struct {
	int state;
	int distance;
	int predecessor;
} vertex;

vertex verticies[MAXG];

void insert_node(node **n, int x);
void delete_node(node **n, int x);
void init_graph(graph *g, int v);
void insert_edge(graph *g, int x, int y, int d);
void delete_edge(graph *g, int x, int y, int d);
void read_graph(graph *g);
void print_graph(graph *g);
void init_search(graph *g);
void bfs(graph *g, int s);
void dfs(graph *g, int s);
void pp_r(int x, int y);
void print_path(int x, int y);

#endif
