#include <string.h>
#include <stdio.h>

int main(void)
{
	char name1[] = {"xyz"};
	char name2[] = {'x', 'y', 'z', '\0'};

	if (!strcmp(name1, name2)) {
		printf("=\n");
	}

	return 0;
}
