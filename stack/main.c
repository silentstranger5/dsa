#include "stack.h"
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
	char str[100];
	stack s;

	init_stack(&s);
	while (scanf("%s", str) > 0) {
		lower(str);
		if (!strcmp(str, "push")) {
			assert(scanf("%d", &i));
			push(&s, i);
		} else if (!strcmp(str, "pop")) {
			printf("%d\n", pop(&s));
		} else if (!strcmp(str, "empty")) {
			printf("stack is %s empty\n", (empty_stack(&s)) ?
					"\b" : "not");
		} else if (!strcmp(str, "print")) {
			print_stack(&s);
		} else if (!strcmp(str, "exit")) {
			break;
		} else if (!strcmp(str, "help")) {
			printf("usage: command [argument]\n"
					"push i - push i to stack\n"
					"pop    - pop  i from stack\n"
					"empty  - check if stack is empty\n"
					"print  - print stack\n"
					"exit   - exit from program\n"
					"help   - display this message\n");
		} else {
			printf("unknown command: %s\n", str);
		}
	}
	return 0;
}
