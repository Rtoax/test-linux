// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "bfd_helpers.h"

void tl_bfd_init(void)
{
#if defined(BFD_INIT_RET_INIT_MAGIC)
	int ret;
	ret = bfd_init();
	if (ret != BFD_INIT_MAGIC) {
		fprintf(stderr, "bfd_init failed.\n");
		exit(1);
	}
#else
	bfd_init();
#endif
}

void tl_bfd_print_build_id(const struct bfd_build_id *bid)
{
	int i;
	for (i = 0; i < bid->size; i++)
		printf("%02x", bid->data[i]);
}

const char *tl_bfd_strbid(const struct bfd_build_id *bid, char *buf, int blen)
{
	int i;

	/* 1 for '\0' */
	if (bid->size * 2 + 1 > blen) {
		return NULL;
	}

	for (i = 0; i < bid->size && i * 2 < blen; i++)
		sprintf(buf + i * 2, "%02x", bid->data[i]);
	buf[i * 2] = '\0';

	return buf;
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
