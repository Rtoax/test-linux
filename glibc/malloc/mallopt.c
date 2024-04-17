#include <stdio.h>
#include <malloc.h>
#include <string.h>


int main(int argc, char * argv[])
{
	char *ptr;
	const char *src = "mcheck test";

	mallopt(M_CHECK_ACTION, 3);

	ptr = (char *)malloc(sizeof(char) * 32);

	memcpy(ptr, src, strlen(src));

	/* overflow here */
	ptr[32] = '\0';
	printf("*ptr = %s\n", ptr);

	free(ptr);
	return 0;
}

