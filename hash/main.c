#include "hash.h"
#include <ctype.h>
#include <string.h>

void lower (char *s)
{
	while (*s) {
		*s = tolower(*s);
		s++;
	}
}

int main(void)
{
	char c;
	char s[STRSIZE];
	char t[STRSIZE];
	char u[STRSIZE];
	node *n;

	while (scanf("%s", s) > 0) {
		lower(s);
		if (!strcmp(s, "put")) {
			assert(scanf(" %c", &c));
			ungetc(c, stdin);
			if (c == '\"') {
				assert(scanf(" \"%[^\"]\"", t));
				assert(scanf(" \"%[^\"]\"", u));
			} else {
				assert(scanf("%s", t));
				assert(scanf("%s", u));
			}
			put_hash(t, u);
		} else if (!strcmp(s, "delete")) {
			assert(scanf("%s", t));
			delete_hash(t);
		} else if (!strcmp(s, "search")) {
			assert(scanf(" %c", &c));
			ungetc(c, stdin);
			if (c == '\"') {
				assert(scanf(" \"%[^\"]\"", t));
			} else {
				assert(scanf("%s", t));
			}
			if (n = get_hash(t)) {
				printf("%s: %s\n", n->k, n->v);
			} else {
				printf("%s is not found\n", t);
			}
		} else if (!strcmp(s, "list")) {
			list_keys();
		} else if (!strcmp(s, "exit")) {
			break;
		} else if (!strcmp(s, "help")) {
			printf("usage: command [arg]\n"
					"put  k v - put i in hash table\n"
					"delete k - delete i from hash table\n"
					"search k - check if i in hash table\n"
					"list     - list all key value pairs\n"
					"exit     - exit from program\n"
					"help     - display this message\n"
			      );
		} else {
			printf("unknown command: %s\n", s);
		}
	}
	return 0;
}
