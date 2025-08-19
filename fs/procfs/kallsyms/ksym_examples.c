#include <stdio.h>
#include <string.h>
#include "ksym_helpers.h"


static struct ksyms *ksyms = NULL;

void assert_find(const char *ksym)
{
	const char *name;
	unsigned long off, off2 = 0xf;
	long addr = ksym_addr(ksyms, ksym);

	if (addr == INVALID_ADDR) {
		printf("%s is not found.\n", ksym);
		return;
	}

	name = ksym_name(ksyms, addr + off2, &off);

	printf("%s %lx (%s+%#lx)\n", ksym, addr, name, off);

	if (strcmp(name, ksym) || off != off2)
		fprintf(stderr, "ERROR: %s != %s or %lx != %lx\n",
			ksym, name, off, off2);
}

int main(void)
{
	ksyms = load_kallsyms();

	assert_find("schedule");
	assert_find("net_tx_action");

	free_kallsyms(ksyms);

	return 0;
}
