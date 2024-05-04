#include <stdio.h>

int parenthesis(char *s)
{
	int i;

	for (i = 0; i >= 0 && *s; s++) {
		if (*s == '(')
			i++;
		else if (*s == ')')
			i--;
	}
	return i;
}

int main(void)
{
	char s[1024];

	while (gets_s(s, 1024) > 0) {
		printf("string is %s balanced\n",
				parenthesis(s) ? "not" : "\b");
	}
	return 0;
}
