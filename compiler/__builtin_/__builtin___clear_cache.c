#include <stdio.h>
#include <malloc.h>

int main(void)
{
	char *str = malloc(sizeof(char) * 1024);
	__builtin___clear_cache(str, str + 1024);
	free(str);
	return 0;
}
