#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	char *a = "123abc";

	printf("%f\n", atof(a));
	printf("%ld\n", atol(a));
	printf("%Ld\n", atoll(a));

	return 0;
}
