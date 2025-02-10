#pragma once

#include <stdbool.h>
#include <sys/types.h>

/* /proc/PID/comm */
const char *proc_comm(char *buf, size_t buf_len);

/* /proc/PID/maps */
unsigned long proc_maps_exec_base_addr(unsigned long *size);
unsigned long proc_maps_exec_text_addr(unsigned long *size);
unsigned long proc_maps_exec_data_addr(unsigned long *size);
unsigned long proc_maps_libc_base_addr(unsigned long *size);
unsigned long proc_maps_libc_base_addr_2(size_t *size);
unsigned long proc_maps_libc_data_addr(unsigned long *size);
unsigned long proc_maps_libc_text_addr(unsigned long *size);
char *proc_maps_libc_base_name(char *buf, size_t buf_len);
unsigned long proc_maps_vdso_addr(unsigned long *size);
unsigned long proc_maps_vvar_addr(unsigned long *size);
unsigned long proc_find_vma_hole(unsigned long start, unsigned long len);
void proc_pid_maps_display(void);
void proc_pid_maps_display_2(FILE *out, char *pfx);
int proc_vdso_dump(const char *filename, unsigned long *vdso_addr,
		   size_t *vdso_size);
int map_new_vdso(const char *vdsoelf, void *addr, size_t size, bool anon);

/* /proc/PID/mem */
int open_proc_pid_mem(pid_t pid);
int proc_pid_mem_read(int mem_fd, off_t paddr, void *buf, size_t len);
int proc_pid_mem_write(int mem_fd, off_t paddr, void *src, size_t len);

/* /proc/mounts */
int proc_for_each_mnt_point(void (*callback)(const char *mnt_point));
