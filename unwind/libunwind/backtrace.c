/**
 *	https://blog.csdn.net/Rong_Toa/article/details/110846509
 *
 *	gcc -g libunwind_backtrace.c -lunwind
 *	Rong Tao
 *	
 */

#include <stdio.h>
#define UNW_LOCAL_ONLY
#include <libunwind.h>
 
void do_backtrace()
{
	unw_cursor_t    cursor;
	unw_context_t   context;
 
	unw_getcontext(&context);
	unw_init_local(&cursor, &context);
 
	while (unw_step(&cursor) > 0) {
		unw_word_t  offset, pc;
		char        fname[64];
 
		unw_get_reg(&cursor, UNW_REG_IP, &pc);
 
		fname[0] = '\0';
		(void) unw_get_proc_name(&cursor, fname, sizeof(fname), &offset);
 
		printf ("%p : (%s+0x%x) [%p]\n", pc, fname, offset, pc);
	}
}

void func1()
{
	do_backtrace();
}

void func2()
{
	func1();
}

int main()
{
	func2(); 
}
