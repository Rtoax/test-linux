#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <errno.h>
#include <unistd.h>
#include <elf.h>

#include "proc.h"

static void mnt_point_callback(const char *mnt_point)
{
	printf("MNT: %s\n", mnt_point);
}

void test_mem_fd(void)
{
	int mem_fd;
	char buf[512];
	Elf64_Ehdr *pehdr;
	unsigned long addr;

	addr = proc_elf_base_addr();

	mem_fd = open_proc_pid_mem(getpid());
	proc_pid_mem_read(mem_fd, addr, buf, sizeof(*pehdr));
	pehdr = (void *)buf;
	printf("e_ident = %s\n", pehdr->e_ident);
	pehdr->e_ident[EI_MAG1] = 'A';
	pehdr->e_ident[EI_MAG2] = 'B';
	pehdr->e_ident[EI_MAG3] = 'C';
	proc_pid_mem_write(mem_fd, addr, pehdr, sizeof(*pehdr));

	memset(buf, 0x0, sizeof(buf));
	proc_pid_mem_read(mem_fd, addr, buf, sizeof(*pehdr));
	pehdr = (void *)buf;
	printf("e_ident = %s\n", pehdr->e_ident);
	if (pehdr->e_ident[EI_MAG1] != 'A' ||
	    pehdr->e_ident[EI_MAG2] != 'B' ||
	    pehdr->e_ident[EI_MAG3] != 'C') {
		fprintf(stderr, "ERROR: Write /proc/%d/mem failed.\n", getpid());
		exit(1);
	}

	close(mem_fd);
}

int main(void)
{
	char comm[128], name[512];

	proc_for_each_mnt_point(mnt_point_callback);

	print_proc_pid_maps();
	printf("comm : %s\n", proc_comm(comm, sizeof(comm)));
	printf("base addr : %lx\n", proc_elf_base_addr());
	printf("libc name : %s\n", proc_elf_base_libc_name(name, sizeof(name)));
	printf("libc addr : %lx\n", proc_elf_base_libc_addr());
	printf("vdso addr : %lx\n", proc_elf_base_vdso_addr());

	test_mem_fd();

	return 0;
}

