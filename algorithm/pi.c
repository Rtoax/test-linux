#include <stdio.h>
#include "unused.h"

double caculate_pi(long int accuracy)
{
	long int i;
	double result = 1;
	double a = 2;
	double b = 1;

	for (i = 0; i < accuracy; i++) {
		result = a / b * result;
		if (a < b) {
			a = a + 2;
		} else if(b < a) {
			b = b + 2;
		}
	}
	return result * 2;
}

int main(void)
{
	double __unused pi = caculate_pi(500000000);
	printf("pi = %.30lf\n", pi);
	return 0;
}
