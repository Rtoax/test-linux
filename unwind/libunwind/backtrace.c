#include <stdio.h>
#define UNW_LOCAL_ONLY
#include <libunwind.h>

void do_backtrace(void)
{
	unw_cursor_t cursor;
	unw_context_t context;

	unw_getcontext(&context);
	unw_init_local(&cursor, &context);

	while (unw_step(&cursor) > 0) {
		unw_word_t offset;
		unw_word_t pc, sp, eax, ebx, ecx, edx;
		char fname[64];

		unw_get_reg(&cursor, UNW_REG_IP,  &pc);
		unw_get_reg(&cursor, UNW_REG_SP,  &sp);
		unw_get_reg(&cursor, UNW_X86_64_RAX, &eax);
		unw_get_reg(&cursor, UNW_X86_64_RDX, &edx);
		unw_get_reg(&cursor, UNW_X86_64_RCX, &ecx);
		unw_get_reg(&cursor, UNW_X86_64_RBX, &ebx);

		fname[0] = '\0';
		unw_get_proc_name(&cursor, fname, sizeof(fname), &offset);
		printf ("%p : (%s+0x%lx) [pc:%p] [sp:%p]\n", (void *)pc, fname,
			offset, (void *)pc, (void *)sp);
		printf("\tEAX=0x%08lx EDX=0x%08lx ECX=0x%08lx EBX=0x%08lx\n",
			eax, edx, ecx, ebx);
	}
}

void func1(void)
{
	do_backtrace();
}

void func2(void)
{
	func1();
}

int main(void)
{
	func2();
	return 0;
}
