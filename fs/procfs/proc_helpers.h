// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#pragma once
#include <stdbool.h>
#include <sys/types.h>

/* /proc/PID */
bool proc_exist(pid_t pid);

/* /proc/PID/comm */
const char *proc_comm(char *buf, size_t buf_len);
const char *proc_pid_comm(pid_t pid, char *buf, size_t buf_len);

/* /proc/PID/status */
int proc_pid_state(pid_t pid);
int proc_state(void);

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

/* /proc/PID/fd/ */
void proc_pid_fds_display(pid_t pid);

/* /proc/mounts */
struct proc_mountpoint {
	char fsname[128];
	char mountpoint[512];
	char fstype[64];
	char mntoptions[256];
	int dump_frequency;
	int fsck_order;
};

int proc_for_each_mount(void (*callback)(const struct proc_mountpoint *mnt,
					 void *arg), void *arg);

pid_t get_pid_from_proc_self(void);
pid_t get_tid_from_proc_thread_self(void);
