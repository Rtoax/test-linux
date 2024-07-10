#include <stdio.h>

#if defined(__x86_64__)
void native_flush_tlb_one_user(unsigned long addr)
{
	//...
	asm volatile("invlpg (%0)" ::"r" (addr) : "memory");
	//...
}
#else
# define native_flush_tlb_one_user(addr)
#endif

int main(int argc, char *argv[])
{
	int a = 10000000;

	while (a--);

	/**
	 * SEGV
	 */
	native_flush_tlb_one_user((unsigned long)&a);

	return 0;
}
