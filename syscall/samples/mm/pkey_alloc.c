#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <sys/mman.h>


int main(void)
{
	int pkey;

	pkey = pkey_alloc(0, 0);

	/* TODO */

	pkey_free(pkey);

	return 0;
}
