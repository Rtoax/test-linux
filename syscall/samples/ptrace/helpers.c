#include <stdio.h>
#include <sys/user.h>


#define debug(fmt...) do { \
		fprintf(stderr, "[%s:%s %d]", __FILE__, __func__, __LINE__); \
		fprintf(stderr, fmt); \
	} while(0)

#ifdef __x86_64__
void print_user_regs_struct(struct user_regs_struct *regs)
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
#else
void print_user_regs_struct(struct user_regs_struct *regs)
{
	printf("Only support X86-64 arch linux OS.\n");
}
#endif

