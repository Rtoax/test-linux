#include <string.h>
#include <stdio.h>

int main(void)
{
	char name[] = {"abcdefg"};

	printf("%s\n", strstr(name, "cd"));

	return 0;
}
