#include <stdio.h>
#include <string.h>
#include "ksym_helpers.h"


static struct ksyms *ksyms = NULL;

void assert_find(const char *ksym)
{
	const char *name;
	unsigned long off;
	long addr = ksym_addr(ksyms, ksym);
	if (addr != INVALID_ADDR) {
		name = ksym_name(ksyms, addr + 0xf, &off);
		printf("%s %lx (%s+%#lx)\n", ksym, addr, name, off);
		if (strcmp(name, ksym)) {
			fprintf(stderr, "ERROR: %s != %s\n", ksym, name);
		}
	} else
		printf("%s is not found.\n", ksym);
}

int main(void)
{
	ksyms = load_kallsyms();

	assert_find("schedule");
	assert_find("net_tx_action");

	free_kallsyms(ksyms);

	return 0;
}
