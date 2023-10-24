#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include "tests.h"

static void *lib = NULL;
static char *(*my_strchr)(char const *, char) = NULL;

static void setup(void)
{
	lib = dlopen("./libasm.so", RTLD_LAZY);
	my_strchr = dlsym(lib, "strchr");
}

static void teardown(void)
{
	dlclose(lib);
	lib = NULL;
	my_strchr = NULL;
}

Test(strchr, match, .init = setup, .fini = teardown)
{
	char *test = "SAUIYIYIYIYSGFSA";
	void *a = 0;
	void *b = 0;

	a = my_strchr(test, 'A');
	b = strchr(test, 'A');
	cr_assert_eq(a, b);
	a = my_strchr(test, 'Q');
	b = strchr(test, 'Q');
	cr_assert_eq(a, b);
	a = my_strchr(test, 0);
	b = strchr(test, 0);
	cr_assert_eq(a, b);
}
