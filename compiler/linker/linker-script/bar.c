#include "bar.h"
#include "foo.h"

static int bar_local_bss1;
static int bar_local_bss2;

static int bar_local_data1 = 1;
static int bar_local_data2 = 1;

int bar_global_bss1;
int bar_global_bss2;
int bar_global_data1 = 1;
int bar_global_data2 = 1;

int bar(void)
{
	bar_local_bss1 = 1;
	bar_local_bss2 = 1;
	bar_local_data1 = 1;
	bar_local_data2 = 1;
	bar_global_bss1 = 2;
	bar_global_bss2 = 2;
	bar_global_data1 = 2;
	bar_global_data2 = 2;
	return 0;
}

int bar1(void)
{
	return 0;
}

int bar2(void)
{
	return 0;
}
