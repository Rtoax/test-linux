#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include "tests.h"

static void *lib = NULL;
static int (*my_strlen)(char const *) = NULL;

static void setup(void)
{
	lib = dlopen("./libasm.so", RTLD_LAZY);
	my_strlen = dlsym(lib, "strlen");
}

static void teardown(void)
{
	dlclose(lib);
	lib = NULL;
	my_strlen = NULL;
}

Test(strlen, len, .init = setup, .fini = teardown)
{
	char *str = "un";

	cr_assert_eq(strlen(str), my_strlen(str));
	str = "deux";
	cr_assert_eq(strlen(str), my_strlen(str));
	str = "trois";
	cr_assert_eq(strlen(str), my_strlen(str));
	str = "quatre";
	cr_assert_eq(strlen(str), my_strlen(str));
	str = "";
	cr_assert_eq(strlen(str), my_strlen(str));
}
