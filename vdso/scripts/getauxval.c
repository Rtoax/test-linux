/**
 * File: getauxval.c
 * AUthor: Rong Tao <rtoax@foxmail.com>
 * Date: 2022.05.09
 *
 * Get vDSO aux vector.
 *
 * You can check 'create_elf_tables.bt' scription.
 *
 * History:
 * 2022.05.11 Rong Tao
 *	Output [vdso] to file.
 * 2022.05.12 Rong Tao
 *	Print /proc/PID/auxv AT_SYSINFO_EHDR item.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/auxv.h>

#define VDSO_FILE_NAME "vDSO-VMA.out"

int main(int argc, char *argv[])
{
	char buffer[256];
	char *cmd, *auxv;
	uintptr_t vdso;
	FILE *fp;

	vdso = (uintptr_t) getauxval(AT_SYSINFO_EHDR);
	printf("getauxval: \033[1;31m0x%016lx\033[m\n", vdso);

	/* Print /proc/PID/maps [vdso] item */
	cmd = buffer;
	snprintf(cmd, sizeof(buffer), "cat /proc/%d/maps | grep vdso]$", getpid());
	system(cmd);

	/* Read /proc/PID/auxv */
	auxv = buffer;
	snprintf(auxv, sizeof(buffer), "/proc/%d/auxv", getpid());
	fp = fopen(auxv, "r");
	while (!feof(fp)) {
		unsigned long type, value;
		fread(&type, sizeof(unsigned long), 1, fp);
		fread(&value, sizeof(unsigned long), 1, fp);
		//printf("%016lx %016lx\n", type, value);
		if (type == AT_SYSINFO_EHDR) {
			printf("%s: \033[1;31m0x%016lx\033[m\n", auxv, value);
			break;
		}
	}
	fclose(fp);

	/* Output vDSO VMA to File */
	fp = fopen(VDSO_FILE_NAME, "w");
	fwrite((void *)vdso, getpagesize() * 4, 1, fp);
	fclose(fp);

	return 0;
}
