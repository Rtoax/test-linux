#include <stdio.h>
#include <sys/user.h>
#include <syscall.h>

#define debug(fmt...) do { \
		fprintf(stderr, "[%s:%s %d]", __FILE__, __func__, __LINE__); \
		fprintf(stderr, fmt); \
	} while(0)

#include "../nr2s.h"

const char *find_syscall_symbol(int code)
{
	return syscall_str[code].name;
}

#ifdef __x86_64__
void print_registers(struct user_regs_struct *regs)
{
	printf("r15     = 0x%016llx\n", regs->r15);
	printf("r14     = 0x%016llx\n", regs->r14);
	printf("r13     = 0x%016llx\n", regs->r13);
	printf("r12     = 0x%016llx\n", regs->r12);
	printf("rbp     = 0x%016llx\n", regs->rbp);
	printf("rbx     = 0x%016llx\n", regs->rbx);
	printf("r11     = 0x%016llx\n", regs->r11);
	printf("r10     = 0x%016llx\n", regs->r10);
	printf("r9      = 0x%016llx\n", regs->r9);
	printf("r8      = 0x%016llx\n", regs->r8);
	printf("rax     = 0x%016llx\n", regs->rax);
	printf("rcx     = 0x%016llx\n", regs->rcx);
	printf("rdx     = 0x%016llx\n", regs->rdx);
	printf("rsi     = 0x%016llx\n", regs->rsi);
	printf("rdi     = 0x%016llx\n", regs->rdi);
	printf("orig_rax = 0x%016llx\n", regs->orig_rax);
	printf("rip     = 0x%016llx\n", regs->rip);
	printf("cs      = 0x%016llx\n", regs->cs);
	printf("eflags  = 0x%016llx\n", regs->eflags);
	printf("rsp     = 0x%016llx\n", regs->rsp);
	printf("ss      = 0x%016llx\n", regs->ss);
	printf("fs_base = 0x%016llx\n", regs->fs_base);
	printf("gs_base = 0x%016llx\n", regs->gs_base);
	printf("ds      = 0x%016llx\n", regs->ds);
	printf("es      = 0x%016llx\n", regs->es);
	printf("fs      = 0x%016llx\n", regs->fs);
	printf("gs      = 0x%016llx\n", regs->gs);
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
#else
void print_registers(struct user_regs_struct *regs)
{
	printf("Only support X86-64 arch linux OS.\n");
}
#endif
