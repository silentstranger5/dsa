#include "heap.h"
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
	int  i;
	heap h;
	char str[100];

	init_heap(&h);
	while (scanf("%s", str) > 0) {
		lower(str);
		if (!strcmp(str, "insert")) {
			assert(scanf("%d", &i));
			insert_heap(&h, i);
		} else if (!strcmp(str, "delete")) {
			assert(scanf("%d", &i));
			delete_heap(&h, i);
		} else if (!strcmp(str, "search")) {
			assert(scanf("%d", &i));
			printf("value %d %s found in the heap\n", i,
					(search_heap(&h, i) >= 0) ? "\b" : "not");
		} else if (!strcmp(str, "empty")) {
			printf("heap is %s empty\n",
					(empty_heap(&h)) ? "\b" : "not");
		} else if (!strcmp(str, "peek")) {
			if (i = peek_heap(&h))
				printf("%d\n", i);
			else
				printf("heap is empty\n");
		} else if (!strcmp(str, "mode")) {
			assert(scanf("%s", str));
			if (!strcmp(str, "get"))
				printf("%s\n", (h.mode) ?
						"max" : "min");
			else if (!strcmp(str, "set")) {
				assert(scanf("%s", str));
				if (!strcmp(str, "min")) {
					h.mode = 0;
					build_heap(&h);
				} else if (!strcmp(str, "max")) {
					h.mode = 1;
					build_heap(&h);
				} else {
					printf("set mode: invalid argument %s\n", str);
				}
			} else {
				printf("mode: invalid argument %s\n", str);
			}
		} else if (!strcmp(str, "print")) {
			print_heap(&h);
		} else if (!strcmp(str, "exit")) {
			break;
		} else if (!strcmp(str, "help")) {
			printf("usage: command [argument]\n"
					"insert i - insert i at the heap\n"
					"delete i - delete i from the heap\n"
					"search i - search i at the heap\n"
					"empty    - check if heap is empty\n"
					"peek     - peek at the top of the heap\n"
					"mode   m - interact with heap mode\n"
					"  get    - get heap mode\n"
					"  set    - set heap mode\n"
					"print    - print the heap\n"
					"exit     - exit from program\n"
					"help     - display this message\n");
		} else {
			printf("unknown command: %s\n", str);
		} 
	}
	return 0;
}
