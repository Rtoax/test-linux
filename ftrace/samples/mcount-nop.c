#include <stdio.h>

#define __visible_default	__attribute__((visibility("default")))
/* forbid mcount call mcount() it self */
#define __no_instr		__attribute__((no_instrument_function))

#define __pg_	__visible_default __no_instr

#define print_func() printf("[%s:%d]\n", __func__, __LINE__)

void __pg_ mcount(void)
{
	print_func();
}

void __pg_ _mcount(void)
{
	print_func();
}

void __pg_ __gnu_mcount_nc(void)
{
	print_func();
}

void __pg_ __fentry__(void)
{
	print_func();
}

void __pg_ __cyg_profile_func_enter(void *child, void *parent)
{
	print_func();
}

void __pg_ __cyg_profile_func_exit(void *child, void *parent)
{
	print_func();
}

void __pg_ __monstartup(unsigned long low, unsigned long high)
{
	print_func();
}

void __pg_ _mcleanup(void)
{
	print_func();
}

void __pg_ mcount_restore(void)
{
	print_func();
}

void __pg_ mcount_reset(void)
{
	print_func();
}

#ifdef TEST_MAIN
void foo(void)
{
}

void bar(void)
{
	foo();
}

int main(void)
{
	foo();
	bar();
	return 0;
}
#endif
