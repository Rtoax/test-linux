#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <libgen.h>
#include <errno.h>
#include <unistd.h>
#include <signal.h>
#include <elf.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <setjmp.h>

#include "proc.h"

#define JMP_SKIP	12

jmp_buf vdso_segv_jmp;

void sig_handler(int sig)
{
	longjmp(vdso_segv_jmp, JMP_SKIP);
}

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

	addr = proc_maps_exec_base_addr(NULL);

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

	addr = proc_maps_exec_base_addr(NULL);
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
	unsigned long addr;
	size_t size;

	signal(SIGSEGV, sig_handler);

	proc_for_each_mnt_point(mnt_point_callback);

	proc_pid_maps_display();
	printf("comm : %s\n", proc_comm(comm, sizeof(comm)));
	printf("base addr : %lx\n", proc_maps_exec_base_addr(NULL));
	printf("base text addr : %lx\n", proc_maps_exec_text_addr(NULL));
	printf("base data addr : %lx\n", proc_maps_exec_data_addr(NULL));
	printf("libc name : %s\n", proc_maps_libc_base_name(name, sizeof(name)));
	addr = proc_maps_libc_base_addr_2(&size);
	printf("libc addr : %lx(%lx) size %lx\n", proc_maps_libc_base_addr(NULL), addr, size);
	printf("libc text addr : %lx\n", proc_maps_libc_text_addr(NULL));
	printf("libc data addr : %lx\n", proc_maps_libc_data_addr(NULL));
	addr = proc_maps_vvar_addr(&size);
	printf("vvar addr : %lx, size %lx\n", addr, size);

	/* Test [vdso] */
	{
		int ret;
		size_t size;
		unsigned long addr;
		struct timeval tv;
		const char *vdso = "vdso.elf";
		bool sigfault_1 = false;

		proc_vdso_dump(vdso, &addr, &size);

		/* Test unmap vdso, it's works */
		munmap((void *)addr, size);

		ret = setjmp(vdso_segv_jmp);
		if (ret == JMP_SKIP) {
			printf("INFO: Get sigfault when call gettimeofday()\n");
			sigfault_1 = true;
			goto skip_call_vdso;
		}

		/* After unmap vdso, gettimeofday will be sigfault */
		gettimeofday(&tv, NULL);

skip_call_vdso:
		if (!sigfault_1) {
			fprintf(stderr, "ERROR: gettimeofday() should sigfault after unmap vdso.\n");
			abort();
		}
		map_new_vdso(vdso, (void *)addr, size, true);

		/* Call vdso function again, works fine */
		gettimeofday(&tv, NULL);
		printf("tv_sec = %ld\n", tv.tv_sec);
	}

	proc_pid_maps_display();

	test_mem_fd();
	test_find_vma_hole();

	return 0;
}

