#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>

#include "tests.h"

static void *lib = NULL;
static void (*my_memcpy)(void *, const void *, size_t) = NULL;

static void setup(void)
{
	lib = dlopen("./libasm.so", RTLD_LAZY);
	my_memcpy = dlsym(lib, "memcpy");
}

static void teardown(void)
{
	dlclose(lib);
	lib = NULL;
	my_memcpy = NULL;
}

Test(memcpy, test_each_char_equal, .init=setup, .fini=teardown)
{
	const char src[50] = "http://www.tutorialspoint.com";
	char dest[50];
	char dest2[50];

	memcpy(dest, src, strlen(src)+1);
	my_memcpy(dest2, src, strlen(src)+1);
	for (int j = 0; j < strlen(dest) + 1; j++)
		cr_assert_eq(((char *)dest)[j], ((char *)dest2)[j],
			"memmove failed on %d: %d != %d", j, ((char *)dest)[j],
			((char *)dest2)[j]);
}
