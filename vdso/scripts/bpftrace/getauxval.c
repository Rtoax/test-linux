/**
 * File: getauxval.c
 * AUthor: Rong Tao <rongtao@cestc.cn>
 * Date: 2022.05.09
 *
 * Get vDSO aux vector.
 *
 * You can check 'create_elf_tables.bt' scription.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/auxv.h>

#define VDSO_FILE_NAME "vDSO-VMA.out"

int main(int argc, char *argv[])
{
	char cmd[256];
	uintptr_t vdso;
	FILE *fp;
	int i;

	vdso = (uintptr_t) getauxval(AT_SYSINFO_EHDR);
	printf("AT_SYSINFO_EHDR \033[1;31m0x%lx\033[m\n", vdso);

	/* Print /proc/PID/maps [vdso] item */
	snprintf(cmd, sizeof(cmd), "cat /proc/%d/maps | grep vdso]$", getpid());
	system(cmd);

	/* Output vDSO VMA to File */
	fp = fopen(VDSO_FILE_NAME, "w");
	fwrite((void*)vdso, 4096, 1, fp);
	fclose(fp);

	return 0;
}
