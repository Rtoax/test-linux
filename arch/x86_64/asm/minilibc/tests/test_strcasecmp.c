#include <dlfcn.h>
#include <stdlib.h>
#include <stdio.h>
#include "tests.h"

static void *lib = NULL;
static int (*my_strcasecmp)(char *, char *) = NULL;

static void setup(void)
{
	lib = dlopen("./libasm.so", RTLD_LAZY);
	my_strcasecmp = dlsym(lib, "strcasecmp");
}

static void teardown(void)
{
	dlclose(lib);
	lib = NULL;
	my_strcasecmp = NULL;
}

Test(strcasecmp, all_match, .init = setup, .fini = teardown)
{
	cr_assert_eq(my_strcasecmp("OP", "OP"), strcasecmp("OP", "OP"));
	cr_assert_eq(my_strcasecmp("OP", "AP"), strcasecmp("OP", "AP"));
	cr_assert_eq(my_strcasecmp("OP", "OZ"), strcasecmp("OP", "OZ"));
	cr_assert_eq(my_strcasecmp("AP", "OP"), strcasecmp("AP", "OP"));
	cr_assert_eq(my_strcasecmp("OZ", "OP"), strcasecmp("OZ", "OP"));
	cr_assert_eq(my_strcasecmp("OP", "op"), strcasecmp("OP", "op"));
	cr_assert_eq(my_strcasecmp("OP", "ap"), strcasecmp("OP", "ap"));
	cr_assert_eq(my_strcasecmp("OP", "oz"), strcasecmp("OP", "oz"));
	cr_assert_eq(my_strcasecmp("op", "OP"), strcasecmp("op", "OP"));
	cr_assert_eq(my_strcasecmp("ap", "OP"), strcasecmp("ap", "OP"));
	cr_assert_eq(my_strcasecmp("oz", "OP"), strcasecmp("oz", "OP"));
	cr_assert_eq(my_strcasecmp("OP1", "op"), strcasecmp("OP1", "op"));
	cr_assert_eq(my_strcasecmp("OP", "ap1"), strcasecmp("OP", "ap1"));
	cr_assert_eq(my_strcasecmp("OP1", "oz"), strcasecmp("OP1", "oz"));
	cr_assert_eq(my_strcasecmp("ap", "OP1"), strcasecmp("ap", "OP1"));
	cr_assert_eq(my_strcasecmp("oz1", "OP"), strcasecmp("oz1", "OP"));
}
