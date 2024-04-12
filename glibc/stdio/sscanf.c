#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	int a, b;
	char str[256];

	sscanf("1.2", "%d.%d\n", &a, &b);
	printf("%d, %d\n", a, b);

	sscanf("3 4", "%s\n%d\n", str, &b);
	printf("%s, %d\n", str, b);

	return 0;
}
