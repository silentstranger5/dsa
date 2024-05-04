#include "tree.h"
#include <ctype.h>
#include <string.h>

void lower(char *s)
{
	while (*s) {
		*s = tolower(*s);
		s++;
	}
}

int main(void)
{
	int i;
	char str[100];
	tree *t, *u;

	t = init_tree();
	while (scanf("%s", str) > 0) {
		lower(str);
		if (!strcmp(str, "empty")) {
			printf("tree is %s empty\n",
					(empty_tree(t)) ? "\b" : "not");
		} else if (!strcmp(str, "search")) {
			assert(scanf("%d", &i));
			printf("value %d %s found in the tree\n", i,
					(search_tree(t, i)) ? "\b" : "not");
		} else if (!strcmp(str, "insert")) {
			assert(scanf("%d", &i));
			insert_tree(&t, i);
		} else if (!strcmp(str, "print")) {
			print_tree(t);
			putchar('\n');
		} else if (!strcmp(str, "successor")) {
			assert(scanf("%d", &i));
			u = successor_tree(search_tree(t, i));
			if (u) 
				printf("%d\n", u->item);
			else
				printf("successor of %d not found\n", i);
		} else if (!strcmp(str, "predecessor")) {
			assert(scanf("%d", &i));
			u = predecessor_tree(search_tree(t, i));
			if (u)
				printf("%d\n", u->item);
			else
				printf("predecessor of %d not found\n", i);
		} else if (!strcmp(str, "minimum")) {
			u = minimum_tree(t);
			if (u)
				printf("%d\n", u->item);
			else
				printf("minimum not found\n");
		} else if (!strcmp(str, "delete")) {
			assert(scanf("%d", &i));
			t = delete_tree(t, i);
		} else if (!strcmp(str, "exit")) {
			break;
		} else if (!strcmp(str, "help")) {
			printf("usage: command [argument]\n"
					"empty         - check if tree is empty\n"
					"search i      - check if i is in the tree\n"
					"insert i      - insert i in the tree\n"
					"print         - print tree\n"
					"successor i   - find successor of i\n"
					"predecessor i - find predecessor of i\n"
					"minimum       - find minimum node of the tree\n"
					"exit          - exit from program\n"
					"help          - display this message\n");
		} else {
			printf("unknown command: %s\n", str);
		}
	}
	return 0;
}
