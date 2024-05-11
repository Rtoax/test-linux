#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	char *str = (char*)aligned_alloc(8, getpagesize());

	strcpy(str, "I \033[31m❤\033[m Xue Yuehua!");
	printf("%s\n", str);

	free(str);
	return 0;
}

