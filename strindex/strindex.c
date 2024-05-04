#include <stdio.h>
#include <string.h>

#define L 100

int strindex(char *s, char *t)
{
	int i, j;

	for (i = 0; *(s + i); i++) {
		for (j = 0; *(t + j) && *(s + i + j) == *(t + j); j++)
			;
		if (!*(t + j) && j > 0)
			return i;
	}
	return -1;
}

int getline(char *s, int i)
{
	if (gets_s(s, L) == 0)
		return 0;
	else {
		s[strlen(s) - 1] = '\0';
		return strlen(s);
	}
}

int main(void)
{
	int i;
	char s[L], t[L];

	while (getline(s, L)) {
		getline(t, L);
		if ((i = strindex(s, t)) >= 0)
			printf("true, %d\n", i);
		else
			printf("false\n");
	}
	return 0;
}
