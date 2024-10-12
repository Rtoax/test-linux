#include <stdio.h>
#include <malloc.h>
#include <unistd.h>

typedef int (*puts_fn)(const char *s);
typedef void *(*malloc_fn)(size_t size);
typedef void (*free_fn)(void *ptr);

/**
 * x86_64: R_X86_64_64
 */
int gin;
int gii = 1;
static int gsin;
static int gsii = 1;
void *gp;

int func1(void)
{
	void *p;

	puts_fn puts0 = puts;
	malloc_fn malloc0 = malloc;
	free_fn free0 = free;

	/**
	 * x86_64: R_X86_64_PLT32
	 * aarch64: R_AARCH64_CALL26
	 */
	puts("Hello");
	puts0("Hello");

	p = malloc(1024);
	free(p);

	p = malloc0(1024);
	free0(p);

	return 0;
}
