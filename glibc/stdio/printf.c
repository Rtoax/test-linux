#include <stdio.h>
#include <string.h>

#define STR	"hello world"

int main(void)
{
	int i;

	printf("printf addr 0x%lx\n", (unsigned long)&printf);

	for (i = 0; i <= strlen(STR); i++)
		printf("%3d/%ld  [%.*s]\n", i, strlen(STR), i, STR);

	printf("KB/s \n");

	printf("%*.*d\n", 3, 10, 10);
	printf("%.*s\n", 4, "hello");
	printf("%*s\n", 40, "hell0");
	printf("%*.*s\n", 40, 4, "hell0");

	printf("%.*d\n", 4, 10000);
	printf("%*d\n", 40, 10000);
	printf("%*.*d\n", 40, 4, 10000);

	printf("Hello %.*d %.*d\n", 5, 2, 5, 3);
	return 0;
}
