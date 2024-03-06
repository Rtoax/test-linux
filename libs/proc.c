#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <errno.h>
#include <unistd.h>


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
};

static unsigned long __proc_elf_base_addr(enum vma_type vma_type)
{
	unsigned long addr = 0;
	char maps[128], comm[128];
	FILE *fp;

	snprintf(maps, sizeof(maps) - 1, "/proc/%d/maps", getpid());
	fp = fopen(maps, "r");
	fseek(fp, 0, SEEK_SET);

	do {
		unsigned long start, end, pgoff;
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
			if (!strcmp(basename(name_), "libc.so.6")) {
				addr = start;
				goto found;
			}
			break;
		}
	} while (1);

found:
	fclose(fp);
	return addr;
}

unsigned long proc_elf_base_addr(void)
{
	return __proc_elf_base_addr(VT_COMM);
}

unsigned long proc_elf_base_libc_addr(void)
{
	return __proc_elf_base_addr(VT_LIBC);
}

void print_proc_pid_maps(void)
{
	char cmd[128];
	snprintf(cmd, sizeof(cmd) - 1, "cat /proc/%d/maps", getpid());
	system(cmd);
}

int for_each_mnt_point(void (*callback)(const char *mnt_point))
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

#ifdef TEST

static void mnt_point_callback(const char *mnt_point)
{
	printf("MNT: %s\n", mnt_point);
}

int main(void)
{
	char comm[128];

	for_each_mnt_point(mnt_point_callback);

	print_proc_pid_maps();
	printf("comm : %s\n", proc_comm(comm, sizeof(comm)));
	printf("base addr : %lx\n", proc_elf_base_addr());
	printf("libc addr : %lx\n", proc_elf_base_libc_addr());
	return 0;
}
#endif
