#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char name[256];

	gethostname(name, sizeof(name));

	printf("%s\n", name);

	return 0;
}
