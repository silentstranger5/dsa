#include <math.h>
#include <stdio.h>

double rf(int l)
{
	if (!l)
		return 1;
	else
		return 1 + 1 / rf(l - 1);
}

double pi(int l)
{
	return 3 + 1 / (7 + 1 / (15 + 1 / (292 + 1 / rf(l))));
}

int main(void)
{
	int i;

	printf("%.*g", 1 << 6, pi(1 << 6));
	return 0;
}
