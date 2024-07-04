#pragma once

const char *find_syscall_symbol(int code);
void print_registers(struct user_regs_struct *regs);
