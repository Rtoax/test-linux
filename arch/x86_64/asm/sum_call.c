#include <stdio.h>
#include <inttypes.h>

double sum(double[], uint64_t);

int main(void)
{
	double test[] = { 40.5, 26.7, 21.9, 1.5, -40.5, -23.4 };
	printf("%20.7f\n", sum(test, 6));
	printf("%20.7f\n", sum(test, 2));
	printf("%20.7f\n", sum(test, 0));
	printf("%20.7f\n", sum(test, 3));
	return 0;
}
