#include <stdio.h>

void reverse_string(char *s)
{
	int i, j, l;
	char *p;

	for (i = l = 0; *(s + i); i++, l++)
		;
	for (i = 0, j = l - 2; i < j; i++, j--) {
		if (*(s + i) != *(s + j)) {
			*(s + i) = *(s + i) ^ *(s + j);
			*(s + j) = *(s + i) ^ *(s + j);
			*(s + i) = *(s + i) ^ *(s + j);
		}
	}
}

void reverse_words(char *s)
{
	int i, j, k, l, t;

	for (i = 0; *(s + i); i++) {
		for (j = i; *(s + j) != ' ' && *(s + j) != '\n'; j++)
			;
		t = j;
		for (k = i, l = j - 1; k < l; k++, l--) {
			if (*(s + k) != *(s + l)) {
				*(s + k) = *(s + k) ^ *(s + l);
				*(s + l) = *(s + k) ^ *(s + l);
				*(s + k) = *(s + k) ^ *(s + l);
			}
		}
		i = t;
	}
}

int main(void)
{
	char s[1024];

	gets_s(s, 1024);
	reverse_string(s);
	reverse_words(s);
	printf("%s", s);
	return 0;
}
