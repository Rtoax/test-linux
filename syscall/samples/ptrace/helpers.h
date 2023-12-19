#pragma once

char *find_syscall_symbol(int code);
void print_user_regs_struct(struct user_regs_struct *regs);
