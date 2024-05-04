#include <stdio.h>

int caesar(int c, int s)
{
	if (isalpha(c))
		return ((tolower(c) - 'a' + s) % 26 + 26) % 26 + 'a';
	else 
		return c;
}

int main(int argc, char const *argv[])
{
	int c, i, o;
	FILE *in, *out;

	i = o = 0;
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
					printf("encrypt: illegal option %c\n", c);
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
	i = rand() % 26;
	while ((c = fgetc(in)) > 0)
		fputc(caesar(c, i), out);
	fclose(in);
	fclose(out);
	return 0;
}
