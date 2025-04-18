#include <stdio.h>
#include <malloc.h>

void clean_up(void)
{
	printf("clean up\n");
}

#ifdef ERROR
/* can't use this way */
__attribute__((cleanup(clean_up)))
#endif
void fun(void)
{
	printf("fun\n");
}

void auto_free(void **p)
{
	printf("Auto free pointer. %p\n", *p);
	free(*p);
}

/* cleanup before destructor */
void __attribute__((destructor)) dtor(void)
{
	printf("destructor\n");
}

int main(void)
{
	void *mem1 __attribute__((__cleanup__(auto_free))) = malloc(1024);
	printf("Alloc pointer %p\n", mem1);
	void *mem2 __attribute__((cleanup(auto_free))) = malloc(1024);
	printf("Alloc pointer %p\n", mem2);
	fun();
	return 0;
}

