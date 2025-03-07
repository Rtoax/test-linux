#include "bar.h"
#include "foo.h"

static int foo_local_bss1;
static int foo_local_bss2;

static int foo_local_data1 = 1;
static int foo_local_data2 = 1;

int foo_global_data1 = 1;

int foo(void)
{
	foo_local_bss1 = 1;
	foo_local_bss2 = 1;
	foo_local_data1 = 1;
	foo_local_data2 = 1;
}

int foo1(void)
{
	foo_global_data1 = 2;
	return 0;
}

int foo2(void)
{
	foo_global_data1 = 3;
	return 0;
}
