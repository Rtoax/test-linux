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

void test_find_vma_hole(void)
{
	unsigned long addr, len;

	addr = 0;
	len = 1024;
	addr = proc_find_vma_hole(addr, len);
	printf("vma hole = 0x%016lx ~ 0x%016lx\n", addr, addr + len);

	addr = proc_elf_base_addr();
	len = 1024;
	addr = proc_find_vma_hole(addr, len);
	printf("vma hole = 0x%016lx ~ 0x%016lx\n", addr, addr + len);

	addr = 0x1000;
	len = 1024;
	addr = proc_find_vma_hole(addr, len);
	printf("vma hole = 0x%016lx ~ 0x%016lx\n", addr, addr + len);
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
	test_find_vma_hole();

	return 0;
}

