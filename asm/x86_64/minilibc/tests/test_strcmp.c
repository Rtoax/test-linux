#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include "tests.h"

static void *lib = NULL;
static int (*my_strcmp)(char *, char *) = NULL;

static void setup(void)
{
	lib = dlopen("./libasm.so", RTLD_LAZY);
	my_strcmp = dlsym(lib, "strcmp");
}

static void teardown(void)
{
	dlclose(lib);
	lib = NULL;
	my_strcmp = NULL;
}

static int s(int val)
{
	if (val < 0)
		return (-1);
	if (val > 0)
		return (1);
	return (0);
}

Test(strcmp, match, .init = setup, .fini = teardown)
{
	cr_assert_eq(s(my_strcmp("OP", "OP")), strcmp("OP", "OP"));
	cr_assert_eq(strcmp("OP", "AP"), s(my_strcmp("OP", "AP")));
	cr_assert_eq(strcmp("OP", "OZ"), s(my_strcmp("OP", "OZ")));
	cr_assert_eq(strcmp("AP", "OP"), s(my_strcmp("AP", "OP")));
	cr_assert_eq(strcmp("OZ", "OP"), s(my_strcmp("OZ", "OP")));
	cr_assert_eq(s(my_strcmp("O", "OP")), strcmp("O", "OP"));
	cr_assert_eq(s(my_strcmp("", "OP")), strcmp("", "OP"));
}
