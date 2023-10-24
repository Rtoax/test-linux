#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include "tests.h"

static void *lib = NULL;
static void (*my_memset)(void *, int, size_t) = NULL;

static void setup(void)
{
	lib = dlopen("./libasm.so", RTLD_LAZY);
	my_memset = dlsym(lib, "memset");
}

static void teardown(void)
{
	dlclose(lib);
	lib = NULL;
	my_memset = NULL;
}

Test(memset, init_mem, .init = setup, .fini = teardown)
{
	int size = 100;
	char test1[10] = "asdfghj";
	char test2[10] = "asdfghj";

	memset(test1, 67, 7);
	my_memset(test2, 67, 7);
	for (int i = 0; i < 8; i++) {
		cr_assert_eq(((char *)test1)[i], ((char *)test2)[i],
		"memset failed on %d: %d != %d", i, ((char *)test1)[i],
		((char *)test2)[i]);
	}
}
