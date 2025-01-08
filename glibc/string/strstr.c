#include <string.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	char *s;
	char name[] = {"abcdefg"};

	printf("%s\n", strstr(name, "cd"));
	printf("%s\n", strstr(name, "cd"));

	s = strstr(name, "??");
	if (s)
		abort();

	return 0;
}
