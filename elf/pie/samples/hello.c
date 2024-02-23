#include <stdio.h>
#include "proc.h"

static int static_i_bss;
static int static_i = 2;

void print_addresses(void)
{
	unsigned long base_addr = proc_elf_base_addr();

#define P(sym)	printf("%48s : 0x%016lx (0x%016lx)\n", #sym, \
		      (unsigned long)&(sym), (unsigned long)&(sym) - base_addr);
	P(print_addresses);
	P(print_proc_pid_maps);
	P(static_i_bss);
	P(static_i);
}

int main(void)
{
	printf("Hello\n");
	print_proc_pid_maps();

	print_addresses();

	return 0;
}
