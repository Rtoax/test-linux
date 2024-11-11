#pragma once

#include <sys/types.h>

/* /proc/PID/comm */
const char *proc_comm(char *buf, size_t buf_len);

/* /proc/PID/maps */
unsigned long proc_maps_exec_base_addr(void);
unsigned long proc_maps_libc_base_addr(void);
char *proc_maps_libc_base_name(char *buf, size_t buf_len);
unsigned long proc_maps_libc_text_addr(void);
unsigned long proc_maps_vdso_addr(void);
unsigned long proc_find_vma_hole(unsigned long start, unsigned long len);
void print_proc_pid_maps(void);

/* /proc/PID/mem */
int open_proc_pid_mem(pid_t pid);
int proc_pid_mem_read(int mem_fd, off_t paddr, void *buf, size_t len);
int proc_pid_mem_write(int mem_fd, off_t paddr, void *src, size_t len);

/* /proc/mounts */
int proc_for_each_mnt_point(void (*callback)(const char *mnt_point));
