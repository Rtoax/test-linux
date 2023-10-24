#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include "tests.h"

static void *lib = NULL;
static int (*my_strncmp)(char *, char *, size_t) = NULL;

static void setup(void)
{
	lib = dlopen("./libasm.so", RTLD_LAZY);
	my_strncmp = dlsym(lib, "strncmp");
}

static void teardown(void)
{
	dlclose(lib);
	lib = NULL;
	my_strncmp = NULL;
}

Test(strncmp, test_strncmp, .init = setup, .fini = teardown)
{
	cr_assert_eq(my_strncmp("OP", "OP", 1), strncmp("OP", "OP", 1));
	cr_assert_eq(my_strncmp("OP", "AP", 1), strncmp("OP", "AP", 1));
	cr_assert_eq(my_strncmp("OP", "OZ", 1), strncmp("OP", "OZ", 1));
	cr_assert_eq(my_strncmp("AP", "OP", 1), strncmp("AP", "OP", 1));
	cr_assert_eq(my_strncmp("OZ", "OP", 1), strncmp("OZ", "OP", 1));
	cr_assert_eq(my_strncmp("OP", "OP", 4), strncmp("OP", "OP", 4));
	cr_assert_eq(my_strncmp("OP", "AP", 4), strncmp("OP", "AP", 4));
	cr_assert_eq(my_strncmp("OP", "OZ", 4), strncmp("OP", "OZ", 4));
	cr_assert_eq(my_strncmp("AP", "OP", 4), strncmp("AP", "OP", 4));
	cr_assert_eq(my_strncmp("OZ", "OP", 4), strncmp("OZ", "OP", 4));
	cr_assert_eq(my_strncmp("", "", 4), strncmp("", "", 4));
}
