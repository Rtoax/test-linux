#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
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

unsigned long proc_elf_base_addr(void)
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
		proc_comm(comm, sizeof(comm));
		if (!strcmp(basename(name_), comm)) {
			addr = start;
			break;
		}
	} while (1);

	fclose(fp);
	return addr;
}

void print_proc_pid_maps(void)
{
	char cmd[128];
	snprintf(cmd, sizeof(cmd) - 1, "cat /proc/%d/maps", getpid());
	system(cmd);
}

#ifdef TEST
int main(void)
{
	char comm[128];
	print_proc_pid_maps();
	printf("comm : %s\n", proc_comm(comm, sizeof(comm)));
	printf("base addr : %lx\n", proc_elf_base_addr());
	return 0;
}
#endif
