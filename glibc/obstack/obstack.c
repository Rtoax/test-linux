#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <obstack.h>

#define debug() printf("%s:%d\n",__func__, __LINE__)

void *mymalloc(ssize_t size)
{
	debug();
	return malloc(size);
}

void myfree(void*ptr)
{
	debug();
	free(ptr);
}

#define obstack_chunk_alloc mymalloc
#define obstack_chunk_free myfree

int main(void)
{
	struct obstack obs;
	char *addr;

	obstack_init(&obs);

	printf("root = %d\n", obstack_room(&obs));

	addr = obstack_alloc(&obs, 100);

	printf("root = %d\n", obstack_room(&obs));

	obstack_copy(&obs, addr, 20);

	printf("root = %d\n", obstack_room(&obs));

	obstack_grow(&obs, addr, 300);

	printf("root = %d\n", obstack_room(&obs));

	obstack_free(&obs, addr);
	obstack_finish(&obs);

	printf("root = %d\n", obstack_room(&obs));

	return 0;
}
