#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "helpers.h"

void tl_bfd_print_build_id(const struct bfd_build_id *bid)
{
	int i;
	for (i = 0; i < bid->size; i++)
		printf("%02x", bid->data[i]);
	printf("\n");
}

/* Swap puts@GLIBC_2.34 to puts */
const char *tl_bfd_pure_name(asymbol *sym, char *buf, int blen)
{
	char *name = strstr(sym->name, "@");
	if (!name)
		return sym->name;

	unsigned int len = name - sym->name;
	if (len > blen) {
		fprintf(stderr, "Too short buffer length.\n");
		return NULL;
	}

	strncpy(buf, sym->name, len);
	buf[len] = '\0';

	return buf;
}
