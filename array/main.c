#include "array.h"
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
	int i, j;
	char str[100];
	array a;

	init_array(&a, 1);
	while (scanf("%s", str) >= 0) {
		lower(str);
		if (!strcmp(str, "empty")) {
			printf("array is %s empty\n",
					(empty_array(&a)) ? "\b" : "not");
		} else if (!strcmp(str, "head")) {
			if (i = head_array(&a))
				printf("%d\n", i);
		} else if (!strcmp(str, "prepend")) {
			assert(scanf("%d", &i));
			prepend_array(&a, i);
		} else if (!strcmp(str, "append")) {
			assert(scanf("%d", &i));
			append_array(&a, i);
		} else if (!strcmp(str, "insert")) {
			assert(scanf("%d %d", &i, &j));
			insert_array(&a, i, j);
		} else if (!strcmp(str, "pop")) {
			if (i = pop_array(&a))
				printf("%d\n", i);
		} else if (!strcmp(str, "dequeue")) {
			if (i = dequeue_array(&a))
				printf("%d\n", i);
		} else if (!strcmp(str, "delete")) {
			assert(scanf("%d", &i));
			if (j = delete_array(&a, i))
				printf("%d\n", j);
		} else if (!strcmp(str, "search")) {
			assert(scanf("%d", &i));
			printf("value %d %s found in the array\n", i,
					(search_array(&a, i) > 0) ? "\b" : "not");
		} else if (!strcmp(str, "print")) {
			print_array(&a);
		} else if (!strcmp(str, "exit")) {
			break;
		} else if (!strcmp(str, "help")) {
			printf("usage: command [arg...]\n"
					"empty       - check if array is empty\n"
					"head        - get head of array\n"
					"prepend i   - prepend i to array\n"
					"append  i   - append  i to array\n"
					"insert  i j - insert  i to array at j\n"
					"pop     i   - pop     i from array\n"
					"dequeue i   - dequeue i from array\n"
					"delete  i   - delete    from array at i\n"
					"search  i   - check   i in   array\n"
					"print       - print array\n"
					"exit        - exit from program\n"
					"help        - display this message\n");
		} else {
			printf("unknown command: %s\n", str);
		}
	}
	return 0;
}
