#include "list.h"
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
	list *l, *t;

	l = init_list();
	while (scanf("%s", str) > 0) {
		lower(str);
		if (!strcmp(str, "empty")) {
			printf("list is %s empty\n", empty_list(l) ?
					"\b" : "not");
		} else if (!strcmp(str, "predecessor")) {
			assert(scanf("%d", &i));
			if (t = predecessor_list(l, i))
				printf("%d\n", t->item);
			else
				printf("predecessor not found\n");
		} else if (!strcmp(str, "search")) {
			assert(scanf("%d", &i));
			printf("value %d %s found in the list\n", i,
					(t = search_list(l, i)) ? "\b" : "not");
		} else if (!strcmp(str, "insert")) {
			assert(scanf("%d", &i));
			insert_list(&l, i);
		} else if (!strcmp(str, "delete")) {
			assert(scanf("%d", &i));
			delete_list(&l, i);
		} else if (!strcmp(str, "print")) {
			print_list(l);
		} else if (!strcmp(str, "exit")) {
			break;
		} else if (!strcmp(str, "help")) {
			printf("usage: command [argument]\n"
					"empty         - check if list is empty\n"
					"predecessor i - find predecessor of i in list\n"
					"search      i - check if i is in the list\n"
					"insert      i - insert i in the list\n"
					"delete      i - delete i from the list\n"
					"print         - print list\n"
					"exit          - exit from program\n"
					"help          - display this message\n");
		} else {
			printf("unknown command: %s\n", str);
		}
	}
	return 0;
}
