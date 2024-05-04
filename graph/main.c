#include "graph.h"

int main(void)
{
	int x, y;
	graph g;

	read_graph(&g);
	print_graph(&g);
	init_search(&g);
	assert(scanf("%d %d", &x, &y));
	dfs(&g, x);
	print_path(x, y);
	return 0;
}
