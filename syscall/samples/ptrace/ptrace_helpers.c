// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <stdio.h>
#include <sys/user.h>
#include <syscall.h>

#include "ptrace_helpers.h"

#define debug(fmt...) do { \
		fprintf(stderr, "[%s:%s %d]", __FILE__, __func__, __LINE__); \
		fprintf(stderr, fmt); \
	} while(0)

#include "../nr2s.h"

const char *find_syscall_symbol(int code)
{
	return syscall_str[code].name;
}

#if defined(__x86_64__)
void print_registers(struct user_regs_struct *regs)
{
#define DOUBLE(a) a, a
	printf("r15      = 0x%016llx %lld\n", DOUBLE(regs->r15));
	printf("r14      = 0x%016llx %lld\n", DOUBLE(regs->r14));
	printf("r13      = 0x%016llx %lld\n", DOUBLE(regs->r13));
	printf("r12      = 0x%016llx %lld\n", DOUBLE(regs->r12));
	printf("rbp      = 0x%016llx %lld\n", DOUBLE(regs->rbp));
	printf("rbx      = 0x%016llx %lld\n", DOUBLE(regs->rbx));
	printf("r11      = 0x%016llx %lld\n", DOUBLE(regs->r11));
	printf("r10      = 0x%016llx %lld\n", DOUBLE(regs->r10));
	printf("r9       = 0x%016llx %lld\n", DOUBLE(regs->r9));
	printf("r8       = 0x%016llx %lld\n", DOUBLE(regs->r8));
	printf("rax      = 0x%016llx %lld\n", DOUBLE(regs->rax));
	printf("rcx      = 0x%016llx %lld\n", DOUBLE(regs->rcx));
	printf("rdx      = 0x%016llx %lld\n", DOUBLE(regs->rdx));
	printf("rsi      = 0x%016llx %lld\n", DOUBLE(regs->rsi));
	printf("rdi      = 0x%016llx %lld\n", DOUBLE(regs->rdi));
	printf("orig_rax = 0x%016llx %lld\n", DOUBLE(regs->orig_rax));
	printf("rip      = 0x%016llx %lld\n", DOUBLE(regs->rip));
	printf("cs       = 0x%016llx %lld\n", DOUBLE(regs->cs));
	printf("eflags   = 0x%016llx %lld\n", DOUBLE(regs->eflags));
	printf("rsp      = 0x%016llx %lld\n", DOUBLE(regs->rsp));
	printf("ss       = 0x%016llx %lld\n", DOUBLE(regs->ss));
	printf("fs_base  = 0x%016llx %lld\n", DOUBLE(regs->fs_base));
	printf("gs_base  = 0x%016llx %lld\n", DOUBLE(regs->gs_base));
	printf("ds       = 0x%016llx %lld\n", DOUBLE(regs->ds));
	printf("es       = 0x%016llx %lld\n", DOUBLE(regs->es));
	printf("fs       = 0x%016llx %lld\n", DOUBLE(regs->fs));
	printf("gs       = 0x%016llx %lld\n", DOUBLE(regs->gs));
#undef DOUBLE
}
#elif defined(__aarch64__)
void print_registers(struct user_regs_struct *regs)
{
	int i;
	for (i = 0; i < 31; i++)
		printf("x%-2d\t0x%016llx %lld\n", i, regs->regs[i], regs->regs[i]);
	printf("sp\t0x%016llx %lld\n", regs->sp, regs->sp);
	printf("pc\t0x%016llx %lld\n", regs->pc, regs->pc);
	printf("pstate\t0x%016llx %lld\n", regs->pstate, regs->pstate);
}
#elif defined(__riscv)
# if __riscv_xlen == 64
void print_registers(struct user_regs_struct *regs)
{
# define P(v) printf(#v"\t0x%016lx %ld\n", regs->v, regs->v);
	P(pc)
	P(ra);
	P(sp);
	P(gp);
	P(tp);
	P(t0);
	P(t1);
	P(t2);
	P(s0);
	P(s1);
	P(a0);
	P(a1);
	P(a2);
	P(a3);
	P(a4);
	P(a5);
	P(a6);
	P(a7);
	P(s2);
	P(s3);
	P(s4);
	P(s5);
	P(s6);
	P(s7);
	P(s8);
	P(s9);
	P(s10);
	P(s11);
	P(t3);
	P(t4);
	P(t5);
	P(t6);
# undef P
}
# else
#  error "Not support riscv32 yet"
# endif
#elif defined(__sw_64__)
# if 0
struct user
{
  unsigned long	int regs[EF_SIZE / 8 + 32];	/* integer and fp regs */
  size_t u_tsize;				/* text size (pages) */
  size_t u_dsize;				/* data size (pages) */
  size_t u_ssize;				/* stack size (pages) */
  unsigned long	int start_code;			/* text starting address */
  unsigned long	int start_data;			/* data starting address */
  unsigned long	int start_stack;		/* stack starting address */
  long int signal;				/* signal causing core dump */
  struct regs *u_ar0;				/* help gdb find registers */
  unsigned long	int magic;			/* identifies a core file */
  char u_comm[32];				/* user command name */
};
# endif
void print_registers(struct user *regs)
{
	int i;
	for (i = 0; i < EF_SIZE / 8 + 32; i++)
		printf("x%-2d\t0x%016lx %ld\n", i, regs->regs[i], regs->regs[i]);
}
#else
void print_registers(struct user_regs_struct *regs)
{
	printf("Only support X86-64 arch linux OS.\n");
}
#endif
