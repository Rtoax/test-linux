#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include "tests.h"

static void *lib = NULL;
static char *(*my_rindex)(const char *s, int c) = NULL;

static void setup(void)
{
	lib = dlopen("./libasm.so", RTLD_LAZY);
	my_rindex = dlsym(lib, "rindex");
}

static void teardown(void)
{
	dlclose(lib);
	lib = NULL;
	my_rindex = NULL;
}

Test(rindex, first_letter, .init = setup, .fini = teardown)
{
	char *test;
	char *b = 0;
	char *a = 0;

	test = "AZERTYUIOP";
	b = rindex(test, 'A');
	a = my_rindex(test, 'A');
	cr_assert_eq(a, b, "rindex failed: %p != %p", a, b);

	b = rindex(test, 'K');
	a = my_rindex(test, 'K');
	cr_assert_eq(a, b, "rindex failed: %p != %p", a, b);

	b = rindex(test, 'a');
	a = my_rindex(test, 'a');
	cr_assert_eq(a, b, "rindex failed: %p != %p", a, b);

	b = rindex(test, ' ');
	a = my_rindex(test, ' ');
	cr_assert_eq(a, b, "rindex failed: %p != %p", a, b);

	b = rindex(test, '\0');
	a = my_rindex(test, '\0');
	cr_assert_eq(a, b, "rindex failed: %p != %p", a, b);
}
