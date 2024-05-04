#include <stdio.h>
#include <stdlib.h>

#define MAX 'e'

typedef struct {
	char *s;
	char *t;
	char *u;
	int l;
} string;

void init_string(string *s)
{
	s->l = 0;
	s->s = NULL;
	s->t = NULL;
	s->u = NULL;
}

void put_char(string *s, char c)
{
	if (!s->s) {
		s->s = malloc(s->l = 2);
		s->t = s->s;
		s->u = s->s;
	} else if (s->t - s->s >= s->l) {
		if ((s->s = realloc(s->s, s->l <<= 1)) == NULL) {
			printf("failed to reallocate string\n");
			return;
		}
		s->t = s->s + (s->l >> 1);
		s->u = s->s;
	}
	*s->t++ = c;
}

int get_char(string *s)
{
	if (*s->u)
		return *s->u++;
	else
		return 0;
}

int caesar(int c, int s)
{
	if (isalpha(c))
		return ((tolower(c) - 'a' + s) % 26 + 26) % 26 + 'a';
	else 
		return c;
}

int main(int argc, char const *argv[])
{
	int d[26];
	int c, f, i, m, o;
	FILE *in, *out;
	string s;

	i = o = 0;
	init_string(&s);
	while (--argc > 0 && **++argv == '-')
		while (c = *++*argv)
			switch (c) {
				case 'i':
					i = 1;
					break;
				case 'o':
					o = 1;
					break;
				default:
					printf("decrypt: illegal option %c\n", c);
					break;
			}
	in = (i) ? fopen(*argv++, "r") : stdin;
	if (!in) {
		printf("failed to open file %s\n", *argv);
		return 1;
	}
	out = (o) ? fopen(*argv++, "w") : stdout;
	if (!out) {
		printf("failed to open file %s\n", *argv);
		return 1;
	}
	for (i = 0; i < 26; i++)
		*(d + i) = 0;
	while ((c = fgetc(in)) > 0) {
		if (in == stdin)
			put_char(&s, c);
		if (isalpha(c))
			(*(d + c - 'a'))++;
	}
	if (in == stdin)
		put_char(&s, '\0');
	for (i = m = 0; i < 26; i++)
		if (*(d + i) > *(d + m))
			m = i;
	f = -abs('a' + m - MAX);
	if (in == stdin) {
		while ((c = get_char(&s)) > 0)
			fputc(caesar(c, f), out);
	} else {
		fseek(in, 0, SEEK_SET);
		while ((c = fgetc(in)) > 0)
			fputc(caesar(c, f), out);
	}
	return 0;
}
