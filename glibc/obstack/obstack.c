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

void pool_info(struct obstack *pool)
{
	printf("chunk size = %ld, room = %d, objsz = %d\n",
		obstack_chunk_size(pool),
		obstack_room(pool),
		obstack_object_size(pool));
}

int main(void)
{
	struct obstack pool;
	char *addr;

	obstack_init(&pool);

	pool_info(&pool);

	addr = obstack_alloc(&pool, 100);

	pool_info(&pool);

	obstack_copy(&pool, addr, 20);

	pool_info(&pool);

	obstack_grow(&pool, addr, 300);

	pool_info(&pool);

	obstack_free(&pool, addr);
	obstack_finish(&pool);

	pool_info(&pool);

	return 0;
}
