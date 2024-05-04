#include <stdio.h>
#include <math.h>

double phi(int l)
{
	if (!l)
		return 1;
	else
		return 1 + (1 / phi(l-1));
}

int main(void)
{
	printf("%.*g\n", 1 << 6, phi(1 << 6));
	printf("%.*g\n", 1 << 6, (1 + sqrt(5)) / 2);
	return 0;
}
