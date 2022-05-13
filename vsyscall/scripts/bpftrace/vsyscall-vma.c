/**
 * File: vsyscall_vma.c
 * AUthor: Rong Tao <rongtao@cestc.cn>
 * Date: 2022.05.13
 *
 * Read [vsyscall] vma and output to file.
 *
 * TODO: [vsyscall] not readable
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

#define VSYSCALL_FILE_NAME "vsyscall-VMA.out"

int main(int argc, char *argv[])
{
	char cmd[256];
	FILE *fp;
	int i, length;
	unsigned long start, end;

	/* Read /proc/PID/maps [vsyscall] item */
	snprintf(cmd, sizeof(cmd), "cat /proc/%d/maps | grep vsyscall]$", getpid());
	fp = popen(cmd, "r");

	start = end = 0;
	while (!feof(fp)) {
		char line[1024];
		unsigned long vm_start, vm_end, offset;
		unsigned int maj, min, inode;
		char perms[5], name[256];
		int ret;

		if (!fgets(line, sizeof(line), fp))
			break;
		ret = sscanf(line, "%lx-%lx %s %lx %x:%x %d %255s",
			&vm_start, &vm_end, perms, &offset, &maj, &min, &inode, name);
		if (!strcmp(name, "[vsyscall]")) {
			start = vm_start;
			end = vm_end;
			if (perms[0] != 'r') {
				/* ffffffffff600000-ffffffffff601000 --xp 00000000 00:00 0 [vsyscall] */
				printf("[vsyscall] not readable, check /proc/self/maps.\n");
				return 1;
			}
			break;
		}
	}
	pclose(fp);

	if (start == 0 || end == 0) {
		printf("Not find [vsyscall] VMA.\n");
		return 1;
	}
	printf("Find [vsyscall]: %lx-%lx, len = %d\n", start, end, length);

	/* Output [vsyscall] VMA to File */
	fp = fopen(VSYSCALL_FILE_NAME, "w");
	length = end - start;
	if ((i = fwrite((void*)start, length, 1, fp)) <= 0) {
		perror("fwrite:");
	}
	fclose(fp);

	return 0;
}
