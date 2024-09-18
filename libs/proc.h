#pragma once

#include <sys/types.h>

/* /proc/PID/comm */
const char *proc_comm(char *buf, size_t buf_len);

/* /proc/PID/maps */
unsigned long proc_elf_base_addr(void);
unsigned long proc_elf_base_libc_addr(void);
char *proc_elf_base_libc_name(char *buf, size_t buf_len);
void print_proc_pid_maps(void);

/* /proc/mounts */
int proc_for_each_mnt_point(void (*callback)(const char *mnt_point));

