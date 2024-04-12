#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <obstack.h>

#define obstack_chunk_alloc malloc
#define obstack_chunk_free free

int main(void)
{
	struct obstack *obs;
	char *addr;

	obstack_init(obs);
	addr = obstack_alloc(obs, 100);

	obstack_copy(obs, addr, 20);
	obstack_free(obs, addr);

	return 0;
}
