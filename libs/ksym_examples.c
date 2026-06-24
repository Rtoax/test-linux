// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "ksym_helpers.h"

static struct ksyms *ksyms = NULL;

void assert_find(const char *ksym)
{
	const char *name;
	unsigned long off, off2 = 0xf;
	long addr = ksym_addr(ksyms, ksym);

	if (addr == INVALID_ADDR || addr == -EINVAL) {
		fprintf(stderr, "%s is not found.\n", ksym);
		return;
	}

	/* If no permission read /proc/kallsyms, the address is zero */
	if (addr == 0) {
		fprintf(stderr, "%s 0x%lx\n", ksym, addr);
		return;
	}

	name = ksym_name(ksyms, addr + off2, &off);

	printf("%s 0x%lx (%s+%#lx)\n", ksym, addr, name, off);

	if (strcmp(name, ksym) || off != off2) {
		fprintf(stderr, "ERROR: %s != %s or 0x%lx != 0x%lx\n",
			ksym, name, off, off2);
		exit(EXIT_FAILURE);
	}
}

int main(int argc, char *argv[])
{
	ksyms = load_kallsyms();

	if (argc > 1) {
		for (int i = 1; i < argc; i++)
			assert_find(argv[i]);
	} else {
		assert_find("schedule");
		assert_find("net_tx_action");
		assert_find("net_rx_action");
	}

	free_kallsyms(ksyms);

	return 0;
}
