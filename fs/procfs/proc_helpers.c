// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
/**
 * This code file only stores some common interfaces, which will exist in
 * other _helpers source code files for different subsystems in the proc file
 * system. For example, for the cgroup subsystem, cgroup parsing of
 * /proc/mounts and /proc/<pid>/cgroup will be done in cgroup_helpers.c.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>
#include <elf.h>
#include <sys/mman.h>
#include <linux/prctl.h>  /* Definition of PR_* constants */
#include <sys/prctl.h>

#include "proc_helpers.h"


#ifdef DEBUG
# define LOG_DEBUG(fmt...) do {	\
		fprintf(stderr, "[%s:%d] ", __func__, __LINE__);	\
		fprintf(stderr, fmt);	\
	} while (0)
#else
# define LOG_DEBUG(fmt...)
#endif

bool proc_exist(pid_t pid)
{
	char proc[64];
	snprintf(proc, sizeof(proc) - 1, "/proc/%d", pid);
	return access(proc, F_OK) == 0;
}

static const char *proc_pid_file_content(pid_t pid, const char *fname,
					 char *buf, size_t buf_len)
{
	char file[128], content[256];
	FILE *fp;

	snprintf(file, sizeof(file) - 1, "/proc/%d/%s", pid, fname);
	fp = fopen(file, "r");
	if (!fp)
		return NULL;
	fseek(fp, 0, SEEK_SET);
	fgets(content, sizeof(content), fp);
	sscanf(content, "%s", buf);
	fclose(fp);

	return buf;
}

const char *proc_pid_comm(pid_t pid, char *buf, size_t buf_len)
{
	return proc_pid_file_content(pid, "comm", buf, buf_len);
}

const char *proc_comm(char *buf, size_t buf_len)
{
	return proc_pid_comm(getpid(), buf, buf_len);
}

enum vma_type {
	VT_COMM,
	VT_LIBC,
	VT_VDSO,	/* [vdso] */
	VT_VVAR,	/* [vvar] */
	VT_HOLE,	/* Not used in memory space */
};

union addr_args {
	/* VT_HOLE */
	struct {
		/* start could be 0 */
		unsigned long start, len;
	} vt_hole_arg;
	int need_prot;
};


static unsigned int perms2prot(char *perms)
{
	unsigned int prot = PROT_NONE;

	if (perms[0] == 'r')
		prot |= PROT_READ;
	if (perms[1] == 'w')
		prot |= PROT_WRITE;
	if (perms[2] == 'x')
		prot |= PROT_EXEC;
	/* Ignore 'p'/'s' flag, we don't need it */
	return prot;
}

static unsigned long __proc_pid_maps_addr(pid_t pid, enum vma_type vma_type,
					  char *get_name, union addr_args *arg,
					  unsigned long *size)
{
	unsigned long addr = 0;
	char maps[128], comm[128];
	FILE *fp;
	unsigned long prev_start, prev_end;
	int vma_count = 0;
	unsigned int prot = PROT_NONE;

	snprintf(maps, sizeof(maps) - 1, "/proc/%d/maps", pid);
	fp = fopen(maps, "r");
	fseek(fp, 0, SEEK_SET);

	prev_start = prev_end = 0;

	do {
		unsigned long start, end;
		unsigned long pgoff;
		unsigned int major, minor;
		unsigned long inode;
		char perms[5], name_[256];
		int r;
		char line[1024];

		start = end = pgoff = major = minor = inode = 0;

		memset(perms, 0, sizeof(perms));
		memset(name_, 0, sizeof(name_));
		memset(line, 0, sizeof(line));

		if (!fgets(line, sizeof(line), fp))
			break;
		r = sscanf(line, "%lx-%lx %s %lx %x:%x %ld %255s",
			   &start, &end, perms, &pgoff, &major, &minor, &inode,
			   name_);
		if (r <= 0) {
			fprintf(stderr, "ERROR: sscanf failed.\n");
			break;
		}

		prot = perms2prot(perms);

		switch (vma_type) {
		case VT_COMM:
			proc_comm(comm, sizeof(comm));
			if (!strcmp(basename(name_), comm)) {
				if (arg && arg->need_prot != PROT_NONE) {
					if ((arg->need_prot & prot) == arg->need_prot) {
						addr = start;
						if (size)
							*size = end - start;
						goto found;
					}
				} else {
					addr = start;
					if (size)
						*size = end - start;
					goto found;
				}
			}
			break;
		case VT_LIBC:
			if (!strcmp(basename(name_), "libc.so.6") ||
			    !strncmp(basename(name_), "libc-", 5)) {
				if (get_name)
					strcpy(get_name, name_);
				if (arg && arg->need_prot != PROT_NONE) {
					if ((arg->need_prot & prot) == arg->need_prot) {
						addr = start;
						if (size)
							*size = end - start;
						goto found;
					}
				} else {
					addr = start;
					if (size)
						*size = end - start;
					goto found;
				}
			}
			break;
		case VT_VDSO:
			if (!strcmp(basename(name_), "[vdso]") ||
			    !strcmp(basename(name_), "[anon:vdso]") ||
			    !strcmp(basename(name_), "[anon:vdso.new]") ||
			    strstr(name_, "vdso.elf") ||
			    strstr(name_, "vdso64.elf")) {
				addr = start;
				if (size)
					*size = end - start;
				if (get_name)
					strcpy(get_name, name_);
				goto found;
			}
			break;
		case VT_VVAR:
			if (!strcmp(basename(name_), "[vvar]")) {
				addr = start;
				if (size)
					*size = end - start;
				if (get_name)
					strcpy(get_name, name_);
				goto found;
			}
			break;
		case VT_HOLE:
			if (!arg) {
				fprintf(stderr, "VT_HOLE need arg.\n");
				abort();
			}

			unsigned long len = arg->vt_hole_arg.len;

			if (arg->vt_hole_arg.start && !prev_start) {
				prev_start = arg->vt_hole_arg.start;
				prev_end = prev_start + len;
			}

			/* Found vma hole */
			if (prev_end && prev_end + len <= start) {
				addr = vma_count == 0 ? prev_start : prev_end;
				/* TODO: Get size */
				goto found;
			}

			/**
			 * FIXME: Hope never found after the last vma
			 */
			break;
		}

		prev_start = start;
		prev_end = end;
		vma_count++;
	} while (1);

found:
	fclose(fp);
	return addr;
}

unsigned long proc_maps_exec_base_addr(unsigned long *size)
{
	return __proc_pid_maps_addr(getpid(), VT_COMM, NULL, NULL, size);
}

unsigned long proc_maps_exec_text_addr(unsigned long *size)
{
	union addr_args arg = {
		.need_prot = PROT_EXEC,
	};
	return __proc_pid_maps_addr(getpid(), VT_COMM, NULL, &arg, size);
}

unsigned long proc_maps_exec_data_addr(unsigned long *size)
{
	union addr_args arg = {
		.need_prot = PROT_READ | PROT_WRITE,
	};
	return __proc_pid_maps_addr(getpid(), VT_COMM, NULL, &arg, size);
}

unsigned long proc_maps_libc_base_addr(unsigned long *size)
{
	return __proc_pid_maps_addr(getpid(), VT_LIBC, NULL, NULL, size);
}

unsigned long proc_maps_libc_data_addr(unsigned long *size)
{
	union addr_args arg = {
		.need_prot = PROT_READ | PROT_WRITE,
	};
	return __proc_pid_maps_addr(getpid(), VT_LIBC, NULL, &arg, size);
}

unsigned long proc_maps_libc_base_addr_2(size_t *size)
{
	unsigned long start, end;
	char maps[256];
	char line[256] = {0};
	FILE *fp;
	char *s;

	/* Match: 7fa55d868000-7fa55d869000 */
	snprintf(maps, 256,
		"grep libc.so.6 /proc/%d/maps | head -1 | grep -o '^[0-9a-z]*-[0-9a-z]*'",
		getpid());

	fp = popen(maps, "r");

	fgets(line, 256, fp);

	start = strtoull(line, NULL, 16);

	s = strstr(line, "-");
	end = strtoull(s + 1, NULL, 16);

	if (size)
		*size = end - start;

	LOG_DEBUG("libc %lx ~ %lx\n", start, end);

	pclose(fp);
	return start;
}

unsigned long proc_maps_libc_text_addr(unsigned long *size)
{
	union addr_args arg = {
		.need_prot = PROT_EXEC,
	};
	return __proc_pid_maps_addr(getpid(), VT_LIBC, NULL, &arg, size);
}

char *proc_maps_libc_base_name(char *buf, size_t buf_len)
{
	__proc_pid_maps_addr(getpid(), VT_LIBC, buf, NULL, NULL);
	return buf;
}

unsigned long proc_maps_vdso_addr(unsigned long *size)
{
	return __proc_pid_maps_addr(getpid(), VT_VDSO, NULL, NULL, size);
}

unsigned long proc_maps_vvar_addr(unsigned long *size)
{
	return __proc_pid_maps_addr(getpid(), VT_VVAR, NULL, NULL, size);
}

unsigned long proc_find_vma_hole(unsigned long start, unsigned long len)
{
	union addr_args arg = {
		.vt_hole_arg.start = start,
		.vt_hole_arg.len = len,
	};
	return __proc_pid_maps_addr(getpid(), VT_HOLE, NULL, &arg, NULL);
}

void proc_pid_maps_display(void)
{
	char cmd[128];
	snprintf(cmd, sizeof(cmd) - 1, "cat /proc/%d/maps", getpid());
	system(cmd);
}

void proc_pid_maps_display_2(FILE *out, char *pfx)
{
	char *line = NULL;
	size_t len = 0;
	FILE *fp;

	if (!out)
		out = stdout;

	if (!pfx)
		pfx = "";

	fp = fopen("/proc/self/maps", "r");
	if (!fp) {
		perror("fopen");
		return;
	}

	while (getline(&line, &len, fp) != -1)
		fprintf(out, "%s%s", pfx, line);
	free(line);
}

int proc_vdso_dump(const char *filename, unsigned long *vdso_addr,
		   size_t *vdso_size)
{
	int mem_fd;
	FILE *fp;
	void *mem;
	size_t size;
	unsigned long addr;

	addr = proc_maps_vdso_addr(&size);
	LOG_DEBUG("vdso addr : %lx, size %lx\n", addr, size);

	mem_fd = open_proc_pid_mem(getpid());
	mem = malloc(size);
	proc_pid_mem_read(mem_fd, addr, mem, size);

	/* Dump [vdso] to vdso.elf */
	fp = fopen(filename, "w");
	fwrite(mem, size, 1, fp);

	free(mem);
	close(mem_fd);
	fclose(fp);

	if (vdso_addr)
		*vdso_addr = addr;
	if (vdso_size)
		*vdso_size = size;

	return 0;
}

int map_new_vdso(const char *vdsoelf, void *addr, size_t size, bool anon)
{
	int fd, mmap_fd, ret = 0;
	void *mem, *buf;
	Elf64_Ehdr *ehdr;
	int flags = MAP_PRIVATE;
	int prot = PROT_READ | PROT_EXEC;

	fd = open(vdsoelf, O_RDONLY);
	if (fd == -1) {
		perror("open\n");
		return -errno;
	}

	LOG_DEBUG("open(%s) = %d\n", vdsoelf, fd);

	mmap_fd = fd;

	if (anon) {
		flags |= MAP_ANONYMOUS;
		/**
		 * If anonymous new vdso, need write permission, see memcpy(3)
		 * below.
		 */
		prot |= PROT_WRITE;

		buf = malloc(size);
		ssize_t n = read(fd, buf, size);
		if (n <= 0) {
			perror("read");
		}
		mmap_fd = -1;
	}

	mem = mmap((void *)addr, size, prot, flags, mmap_fd, 0);
	if (mem == MAP_FAILED) {
		perror("mmap");
		close(fd);
		return -errno;
	}

	if (anon) {
		memcpy(mem, buf, size);
		mprotect(mem, size, PROT_READ | PROT_EXEC);
		LOG_DEBUG("memcpy(%p, %p, %ld)\n", mem, buf, size);
		free(buf);
#ifdef CONFIG_ANON_VMA_NAME
		/**
		 * see manual R_SET_VMA(2const)
		 *
		 * The name can contain only printable ascii characters
		 * (isprint(3)), except '[', ']', '\', '$', and '`'.
		 */
		char *vma_name = "vdso.new";
		LOG_DEBUG("set vdso name to %s", vma_name);
		if (prctl(PR_SET_VMA, PR_SET_VMA_ANON_NAME, addr, size, vma_name) != 0) {
			perror("prctl: PR_SET_VMA_ANON_NAME");
		}
#else
# pragma message("Kernel is not support CONFIG_ANON_VMA_NAME!!!")
#endif
	}

	ehdr = (void *)mem;

	if (ehdr->e_ident[EI_MAG1] != 'E' || ehdr->e_ident[EI_MAG2] != 'L' ||
	    ehdr->e_ident[EI_MAG3] != 'F') {
		fprintf(stderr, "ERROR: %s is not ELF.\n", vdsoelf);
		ret = -EINVAL;
	}

	close(fd);
	return ret;
}

int proc_for_each_mount(void (*callback)(const struct proc_mountpoint *mnt,
					 void *arg), void *arg)
{
	char line[1024];
	FILE *fp;
	struct proc_mountpoint mnt;

	if (!callback)
		return -EINVAL;

	fp = fopen("/proc/mounts", "r");

	while (fgets(line, 1024, fp)) {
		sscanf(line, "%s %s %s %s %d %d\n", mnt.fsname, mnt.mountpoint,
			mnt.fstype, mnt.mntoptions, &mnt.dump_frequency,
			&mnt.fsck_order);
		callback(&mnt, arg);
	}
	fclose(fp);

	return 0;
}

/* close with close(2) */
int open_proc_pid_mem(pid_t pid)
{
	char proc_mem[64];
	int mem_fd;

	sprintf(proc_mem, "/proc/%d/mem", pid);
	mem_fd = open(proc_mem, O_RDWR);
	if (mem_fd <= 0) {
		fprintf(stderr, "ERROR: Open %s failed.\n", proc_mem);
		return -1;
	}
	return mem_fd;
}

int proc_pid_mem_read(int mem_fd, off_t paddr, void *buf, size_t len)
{
	int ret;
	ret = pread(mem_fd, buf, len, paddr);
	if (ret <= 0)
		fprintf(stderr, "ERROR: pread: %m.\n");
	return ret;
}

int proc_pid_mem_write(int mem_fd, off_t paddr, void *src, size_t len)
{
	int ret;
	ret = pwrite(mem_fd, src, len, paddr);
	if (ret <= 0)
		fprintf(stderr, "ERROR: pwrite: %m.\n");
	return ret;
}

void proc_pid_fds_display(int pid)
{
	char buf[256];
	sprintf(buf, "ls -l /proc/%d/fd/", pid);
	system(buf);
}

/**
 * Returns the process ID of the calling processes, as determined from
 * the /proc/self symlink.
 */
pid_t get_pid_from_proc_self(void)
{
	char target[32];
	int pid;
	readlink("/proc/self", target, sizeof(target));
	sscanf(target, "%d", &pid);
	return (pid_t)pid;
}

pid_t get_tid_from_proc_thread_self(void)
{
	char target[64];
	int tid;
	readlink("/proc/thread-self", target, sizeof(target));
	sscanf(target, "%d", &tid);
	return (pid_t)tid;
}
