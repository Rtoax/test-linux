#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <errno.h>
#include <unistd.h>
#include <limits.h>
#include <fcntl.h>

#include "proc.h"

const char *proc_comm(char *buf, size_t buf_len)
{
	char comm[128], content[256];
	FILE *fp;

	snprintf(comm, sizeof(comm) - 1, "/proc/%d/comm", getpid());
	fp = fopen(comm, "r");
	fseek(fp, 0, SEEK_SET);
	fgets(content, sizeof(content), fp);
	sscanf(content, "%s", buf);
	fclose(fp);

	return buf;
}

enum vma_type {
	VT_COMM,
	VT_LIBC,
	VT_VDSO,
	VT_HOLE,	/* Not used in memory space */
};

union addr_args {
	/* VT_HOLE */
	struct {
		/* start could be 0 */
		unsigned long start, len;
	} vt_hole_arg;
};

static unsigned long __proc_maps_addr(enum vma_type vma_type, char *name,
				      union addr_args *arg)
{
	unsigned long addr = 0;
	char maps[128], comm[128];
	FILE *fp;
	unsigned long prev_start, prev_end;
	int vma_count = 0;

	snprintf(maps, sizeof(maps) - 1, "/proc/%d/maps", getpid());
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
		switch (vma_type) {
		case VT_COMM:
			proc_comm(comm, sizeof(comm));
			if (!strcmp(basename(name_), comm)) {
				addr = start;
				goto found;
			}
			break;
		case VT_LIBC:
			if (!strcmp(basename(name_), "libc.so.6") ||
			    !strncmp(basename(name_), "libc-", 5)) {
				addr = start;
				if (name)
					strcpy(name, name_);
				goto found;
			}
			break;
		case VT_VDSO:
			if (!strcmp(basename(name_), "[vdso]")) {
				addr = start;
				if (name)
					strcpy(name, name_);
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

unsigned long proc_elf_base_addr(void)
{
	return __proc_maps_addr(VT_COMM, NULL, NULL);
}

unsigned long proc_elf_base_libc_addr(void)
{
	return __proc_maps_addr(VT_LIBC, NULL, NULL);
}

char *proc_elf_base_libc_name(char *buf, size_t buf_len)
{
	__proc_maps_addr(VT_LIBC, buf, NULL);
	return buf;
}

unsigned long proc_elf_base_vdso_addr(void)
{
	return __proc_maps_addr(VT_VDSO, NULL, NULL);
}

unsigned long proc_find_vma_hole(unsigned long start, unsigned long len)
{
	union addr_args arg = {
		.vt_hole_arg.start = start,
		.vt_hole_arg.len = len,
	};
	return __proc_maps_addr(VT_HOLE, NULL, &arg);
}

void print_proc_pid_maps(void)
{
	char cmd[128];
	snprintf(cmd, sizeof(cmd) - 1, "cat /proc/%d/maps", getpid());
	system(cmd);
}

int proc_for_each_mnt_point(void (*callback)(const char *mnt_point))
{
	char s[2000];
	FILE *f;

	if (!callback)
		return -EINVAL;

	f = fopen("/proc/mounts", "r");

	while (fgets(s, 2000, f)) {
		char *c, *e = s;

		for (c = s; *c; c++) {
			if (*c == ' ') {
				e = c + 1;
				break;
			}
		}

		for (c = e; *c; c++) {
			if (*c == ' ') {
				*c = '\0';
				break;
			}
		}

		callback(e);
	}
	fclose(f);

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
