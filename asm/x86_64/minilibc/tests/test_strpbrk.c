#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include "tests.h"

static void *lib = NULL;
static char *(*my_strpbrk)(const char *s, const char *accept) = NULL;

static void setup(void)
{
	lib = dlopen("./libasm.so", RTLD_LAZY);
	my_strpbrk = dlsym(lib, "strpbrk");
}

static void teardown(void)
{
	dlclose(lib);
	lib = NULL;
	my_strpbrk = NULL;
}

Test(strpbrk, strpbrk1, .init = setup, .fini = teardown)
{
	char *str;
	char *accept;
	char *b = 0;
	char *a = 0;

	str = "AZERTYUIOP";
	accept = "Q";
	b = strpbrk(str, accept);
	a = my_strpbrk(str, accept);
	cr_assert_eq(a, b);
}
