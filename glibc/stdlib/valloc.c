#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	char *str = (char*)valloc(getpagesize());

	strcpy(str, "helloadfasdf");
	printf("str = %s\n", str);

	free(str);
	return 0;
}

