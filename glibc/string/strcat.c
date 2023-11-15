#include <string.h>
#include <stdio.h>
#include <malloc.h>

int main(void)
{
	char string[1024] = {0};

	printf("%s\n", string);

	strcat(string,  "rongtao ");
	printf("%s\n", string);

	strcat(string, "shi");

	printf("%s\n", string);

	return 0;
}
