#pragma once

#if defined(__riscv)
#include <asm/ptrace.h>
#endif

const char *find_syscall_symbol(int code);
#if defined(__sw_64__)
void print_registers(struct user *regs);
#else
void print_registers(struct user_regs_struct *regs);
#endif
