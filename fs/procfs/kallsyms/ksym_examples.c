#include <stdio.h>
#include "ksym_helpers.h"


static struct ksyms *ksyms = NULL;

void assert_find(const char *ksym)
{
	long addr = ksym_addr(ksym, NULL);
	if (addr != INVALID_ADDR)
		printf("%s %lx\n", ksym, addr);
	else
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
