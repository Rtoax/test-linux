#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <errno.h>
#include <unistd.h>

#include "proc.h"

static void mnt_point_callback(const char *mnt_point)
{
	printf("MNT: %s\n", mnt_point);
}

int main(void)
{
	char comm[128];

	proc_for_each_mnt_point(mnt_point_callback);

	print_proc_pid_maps();
	printf("comm : %s\n", proc_comm(comm, sizeof(comm)));
	printf("base addr : %lx\n", proc_elf_base_addr());
	printf("libc addr : %lx\n", proc_elf_base_libc_addr());
	return 0;
}

