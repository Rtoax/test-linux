#include <string.h>
#include <stdio.h>

int main(void)
{
	char name1[] = { "xyz" };
	char name2[] = { 'x', 'y', 'z', '\0' };

	if (!bcmp(name1, name2, sizeof(name1))) {
		printf("=\n");
	}

	return 0;
}
