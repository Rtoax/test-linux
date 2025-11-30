#include <stdio.h>

int main(int argc, char *argv[])
{
	printf("exp(2) %f\n", __builtin_exp(2));
	printf("log(2) %f\n", __builtin_log(2));
	printf("sqrt(2) %f\n", __builtin_sqrt(2));
	return 0;
}
