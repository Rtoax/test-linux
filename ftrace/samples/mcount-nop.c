#include <stdio.h>

#define __visible_default	__attribute__((visibility("default")))
/* forbid mcount call mcount() it self */
#define __no_instr		__attribute__((no_instrument_function))
#define __pg_	__visible_default __no_instr

#define TRACE_DEBUG() do {	\
		void *__return_addr = __builtin_return_address(0);	\
		void *__caller_addr = __builtin_return_address(1);	\
		fprintf(stderr, "[%s:%d] %p %p\n", __func__, __LINE__,	\
			__return_addr, __caller_addr);	\
	} while (0)

void __pg_ mcount(void)
{
	TRACE_DEBUG();
}

void __pg_ _mcount(void)
{
	TRACE_DEBUG();
}

void __pg_ __gnu_mcount_nc(void)
{
	TRACE_DEBUG();
}

void __pg_ __fentry__(void)
{
	TRACE_DEBUG();
}

void __pg_ __cyg_profile_func_enter(void *child, void *parent)
{
	TRACE_DEBUG();
}

void __pg_ __cyg_profile_func_exit(void *child, void *parent)
{
	TRACE_DEBUG();
}

void __pg_ __monstartup(unsigned long low, unsigned long high)
{
	TRACE_DEBUG();
}

void __pg_ _mcleanup(void)
{
	TRACE_DEBUG();
}

void __pg_ mcount_restore(void)
{
	TRACE_DEBUG();
}

void __pg_ mcount_reset(void)
{
	TRACE_DEBUG();
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
#define F(f)	printf("%-32s : %p\n", #f, f);
	F(foo);
	F(bar);
	F(main);

	foo();
	bar();
	return 0;
}
#endif
