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
#else
void print_registers(struct user_regs_struct *regs)
{
	printf("Only support X86-64 arch linux OS.\n");
}
#endif
