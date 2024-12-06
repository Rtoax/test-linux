#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "proc.h"

/**
 * if initialized with 0, is in .bss
 * if initialized with none 0, is in .data
 * if const, is in .rodata
 */

static int static_i_bss;
static int static_i_data = 2;

/**
 * Test bash readline and bpftrace demo, see uprobe.bt
 */
static char *ps1_prompt = "[rongtao@rtoax]$ ";
int readline(const char *ps1, const char *line)
{
	/* Do nothing */
	return 0;
}

void print_addresses(void)
{
	unsigned long base_size;
	unsigned long base_addr = proc_maps_exec_base_addr(&base_size);

#define P(sym)	printf("%48s : 0x%016lx (0x%016lx)\n", #sym, \
		      (unsigned long)&(sym), (unsigned long)&(sym) - base_addr);
	P(print_addresses);
	P(print_proc_pid_maps);
	P(static_i_bss);
	P(static_i_data);
	P(readline);
}

int main(int argc, char *argv[])
{
	int i, secs = 0;

	fprintf(stderr, "Usage: %s [sleep=SEC]\n", argv[0]);

	for (i = 1; i < argc; i++) {
		if (strstr(argv[i], "sleep="))
			secs = atoi(argv[i] + strlen("sleep="));
	}

	printf("Hello\n");
	printf("Pid %d\n", getpid());
	print_proc_pid_maps();

	readline(ps1_prompt, "echo Hello.\n");

	print_addresses();

	if (secs) {
		printf("Sleeping %d seconds ...\n", secs);
		sleep(secs);
	}

	return 0;
}
