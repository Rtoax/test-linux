#include <stdio.h>
#include <malloc.h>

void clean_up(void)
{
	printf("clean up\n");
}

void __attribute__((cleanup(clean_up)))
fun(void)
{
	printf("fun\n");
}

void auto_free(void **p)
{
	printf("Free pointer. %p\n", *p);
	free(*p);
}

int main(void)
{
	void *foo_ptr __attribute__((__cleanup__(auto_free))) = NULL;
	foo_ptr = malloc(1024);
	printf("Alloc pointer %p\n", foo_ptr);
	fun();
	return 0;
}

