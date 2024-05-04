#include "queue.h"
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
	queue q;

	init_queue(&q);
	while (scanf("%s", str) > 0) {
		lower(str);
		if (!strcmp(str, "enqueue")) {
			assert(scanf("%d", &i));
			enqueue(&q, i);
		} else if (!strcmp(str, "dequeue")) {
			printf("%d\n", dequeue(&q));
		} else if (!strcmp(str, "head")) {
			printf("%d\n", head(&q));
		} else if (!strcmp(str, "empty")) {
			printf("queue is %s empty\n", (empty_queue(&q)) ?
					"\b" : "not");
		} else if (!strcmp(str, "print")) {
			print_queue(&q);
		} else if (!strcmp(str, "exit")) {
			break;
		} else if (!strcmp(str, "help")) {
			printf("usage: command [argument]\n"
					"enqueue i - enqueue i to queue\n"
					"dequeue   - dequeue from queue\n"
					"head      - head of queue\n"
					"empty     - check if queue is empty\n"
					"print     - print queue\n"
					"exit      - exit from program\n"
					"help      - display this message\n");
		} else {
			printf("unknown command: %s\n", str);
		}
	}
	return 0;
}
