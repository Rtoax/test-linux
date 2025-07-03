#include <stdio.h>
#include <malloc.h>
#include <string.h>


int main(void)
{
	char *str1 = malloc(64);
	str1 = realloc(str1, 128);

	sprintf(str1, "Hello World.");
	printf("str1 = %s\n", str1);

	char *str2 = strdup(str1);
	printf("str2 = %s\n", str2);

	free(str1);
	free(str2);
	return 0;
}
