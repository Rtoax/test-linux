#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <obstack.h>
#include <pthread.h>


#define NR_THREAD 4

void *mymalloc(ssize_t size)
{
	return malloc(size);
}
void myfree(void *ptr)
{
	free(ptr);
}

#define obstack_chunk_alloc mymalloc
#define obstack_chunk_free myfree
#define obstack_alloc_failed_handler  TODO

char *copystring(struct obstack *obj, char *string)
{
	size_t len = strlen(string) + 1;
	char *s = (char*)obstack_alloc(obj, len);
	memcpy (s, string, len);
	return s;
}

void *routine_task(void *arg)
{
	struct obstack *pobs = (struct obstack *)arg;

	char *str1 = copystring(pobs, "rongtao");
	printf("str1 = %s\n", str1);
	char *str2 = copystring(pobs, "HelloWorld");
	printf("str2 = %s\n", str2);

	obstack_free(pobs, str1);
	obstack_free(pobs, str2);

	char *str3 = (char*)obstack_alloc(pobs, obstack_chunk_size(pobs));
	printf("str3 = %p\n", str3);

	obstack_free(pobs, str3);
	pthread_exit(NULL);
}

int main(void)
{
	int i;
	struct obstack string_obstack;
	pthread_t threadids[NR_THREAD];

	obstack_init(&string_obstack);

	printf("obstack_chunk_size = %ld\n", obstack_chunk_size(&string_obstack));

	for (i = 0; i < NR_THREAD; i++){
		pthread_create(&threadids[i], NULL, routine_task, &string_obstack);
	}

	for (i = 0; i < NR_THREAD; i++){
		pthread_join(threadids[i], NULL);
	}

	obstack_finish(&string_obstack);

	return 0;
}

