#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include "tests.h"

static void *lib = NULL;
static void (*my_memmove)(void *, void *, size_t) = NULL;

static void setup(void)
{
	lib = dlopen("./libasm.so", RTLD_LAZY);
	my_memmove = dlsym(lib, "memmove");
}

static void teardown(void)
{
	dlclose(lib);
	lib = NULL;
	my_memmove = NULL;
}

Test(memmove, right_not_overlap, .init = setup, .fini = teardown)
{

	char dest1[] = "oldstring";
	char dest2[] = "oldstring";
        char src[]  = "newstring";

	memmove(dest1, src, 9);
	my_memmove(dest2, src, 9);
	for (int i = 0; i < 10; i++) {
		cr_assert_eq(((char *)dest1)[i], ((char *)dest2)[i],
		"memmove failed on %d: %d != %d", i, ((char *)dest1)[i],
		((char *)dest2)[i]);
	}
}
