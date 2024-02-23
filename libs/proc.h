#pragma once

const char *proc_comm(char *buf, size_t buf_len);

unsigned long proc_elf_base_addr(void);
unsigned long proc_elf_base_libc_addr(void);

void print_proc_pid_maps(void);
