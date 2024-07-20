#include <malloc.h>

#include "prefetch.h"

int main(void)
{
	char *str = malloc(1024);

	rte_prefetch0(str);

	free(str);
	return 0;
}
