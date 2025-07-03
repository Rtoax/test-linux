#include <stdio.h>

#define __visible_default  __attribute__((visibility("default")))

#define print_func() printf("[%s:%d]\n", __func__, __LINE__)

void __visible_default mcount(void)
{
	print_func();
}

void __visible_default _mcount(void)
{
	print_func();
}

void __visible_default __gnu_mcount_nc(void)
{
	print_func();
}

void __visible_default __fentry__(void)
{
	print_func();
}

void __visible_default __cyg_profile_func_enter(void *child, void *parent)
{
	print_func();
}

void __visible_default __cyg_profile_func_exit(void *child, void *parent)
{
	print_func();
}

void __visible_default __monstartup(unsigned long low, unsigned long high)
{
	print_func();
}

void __visible_default _mcleanup(void)
{
	print_func();
}

void __visible_default mcount_restore(void)
{
	print_func();
}

void __visible_default mcount_reset(void)
{
	print_func();
}
