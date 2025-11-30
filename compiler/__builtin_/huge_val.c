#include <stdio.h>

int main(int argc, char *argv[])
{
	printf("%f\n", __builtin_huge_val());
	return 0;
}
