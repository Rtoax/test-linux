#include <malloc.h>
#include <string.h>
#include "prefetch.h"

int main(void)
{
	char *str = malloc(1024);

	memset(str, 0x0, 1024);
	rte_prefetch0(str);

	free(str);
	return 0;
}
