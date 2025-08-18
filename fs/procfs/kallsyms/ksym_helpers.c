// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (c) 2025 Rong Tao */
#include <assert.h>
#include <errno.h>
#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

#include "ksym_helpers.h"

#define PROC_KALLSYMS	"/proc/kallsyms"


enum ksym_type {
	KSYM_LOCAL_ABS = 1,	/* a */
	KSYM_GLOBAL_ABS,	/* A */
	KSYM_LOCAL_BSS,		/* b */
	KSYM_GLOBAL_BSS,	/* B */
	KSYM_LOCAL_DATA,	/* d */
	KSYM_GLOBAL_DATA,	/* D */
	KSYM_LOCAL_RODATA,	/* r */
	KSYM_GLOBAL_RODATA,	/* R */
	KSYM_LOCAL_FUNC,	/* t */
	KSYM_GLOBAL_FUNC,	/* T */
	KSYM_LOCAL_WEAK_FUNC,	/* w */
	KSYM_GLOBAL_WEAK_FUNC,	/* W */
	KSYM_GLOBAL_WEAK_DATA,	/* V */
	KSYM_GLOBAL_UNKNOWN,	/* ? */
};

struct ksym {
	unsigned long addr;
	enum ksym_type type;
	char *name;
	char *kmod;	/* optional */
};

struct ksyms {
	size_t nsyms;
	void *root_nkta;
	void *root_addr;
};

static struct ksyms ksyms = {0, NULL};


static int ksym_cmp_addr(const void *a1, const void *a2)
{
	const struct ksym *s1 = a1, *s2 = a2;
	return s1->addr - s2->addr;
}

static int ksym_cmp_nkta(const void *a1, const void *a2)
{
	int cmp;
	const struct ksym *s1 = a1, *s2 = a2;
	cmp = strcmp(s1->name, s2->name);
	if (cmp)
		return cmp;
	if (s1->kmod && s2->kmod) {
		cmp = strcmp(s1->kmod, s2->kmod);
		if (cmp)
			return cmp;
	}
	cmp = s1->type - s2->type;
	if (cmp)
		return cmp;
	return ksym_cmp_addr(s1, s2);
}

enum ksym_type c2type(char c_type)
{
	switch (c_type) {
#define CASE(c, e)	case c: return e; break
	CASE('t', KSYM_LOCAL_FUNC);
	CASE('T', KSYM_GLOBAL_FUNC);
	CASE('d', KSYM_LOCAL_DATA);
	CASE('D', KSYM_GLOBAL_DATA);
	CASE('b', KSYM_LOCAL_BSS);
	CASE('B', KSYM_GLOBAL_BSS);
	CASE('r', KSYM_LOCAL_RODATA);
	CASE('R', KSYM_GLOBAL_RODATA);
	CASE('a', KSYM_LOCAL_ABS);
	CASE('A', KSYM_GLOBAL_ABS);
	CASE('w', KSYM_LOCAL_WEAK_FUNC);
	CASE('W', KSYM_GLOBAL_WEAK_FUNC);
	CASE('V', KSYM_GLOBAL_WEAK_DATA);
	CASE('?', KSYM_GLOBAL_UNKNOWN);
#undef CASE
	}
	return KSYM_GLOBAL_UNKNOWN;
}

char type2c(enum ksym_type type)
{
	switch (type) {
#define CASE(c, e)	case e: return c; break
	CASE('t', KSYM_LOCAL_FUNC);
	CASE('T', KSYM_GLOBAL_FUNC);
	CASE('d', KSYM_LOCAL_DATA);
	CASE('D', KSYM_GLOBAL_DATA);
	CASE('b', KSYM_LOCAL_BSS);
	CASE('B', KSYM_GLOBAL_BSS);
	CASE('r', KSYM_LOCAL_RODATA);
	CASE('R', KSYM_GLOBAL_RODATA);
	CASE('a', KSYM_LOCAL_ABS);
	CASE('A', KSYM_GLOBAL_ABS);
	CASE('w', KSYM_LOCAL_WEAK_FUNC);
	CASE('W', KSYM_GLOBAL_WEAK_FUNC);
	CASE('V', KSYM_GLOBAL_WEAK_DATA);
	CASE('?', KSYM_GLOBAL_UNKNOWN);
#undef CASE
	}
	return '?';
}

struct ksym *alloc_ksym(unsigned long addr, enum ksym_type type, char *name,
			char *kmod)
{
	struct ksym *new;

	if (addr == 0 || !name || strlen(name) <= 1)
		return NULL;

	new = malloc(sizeof(struct ksym));

	memset(new, 0, sizeof(struct ksym));
	new->addr = addr;
	new->type = type;
	new->name = strdup(name);
	if (kmod)
		new->kmod = strdup(kmod);

	return new;
}

#if 0
struct ksym *dup_ksym(struct ksym *old)
{
	// TODO
	return NULL;
}
#endif

void free_ksym(struct ksym *ksym)
{
	if (!ksym)
		return;
	free(ksym->name);
	if (ksym->kmod)
		free(ksym->kmod);
	free(ksym);
}

int load_kallsyms(void)
{
	int n;
	FILE *fp;
	unsigned long addr;
	char c_type, s_name[256], s_kmod[128];
	char line[512];

	fp = fopen(PROC_KALLSYMS, "r");
	if (!fp)
		return -errno;

	while (fgets(line, sizeof(line), fp)) {
		memset(s_name, 0, sizeof(s_name));
		memset(s_kmod, 0, sizeof(s_kmod));

		n = sscanf(line, "%lx %c %s %s\n", &addr, &c_type, s_name, s_kmod);
		if (n != 4 && n != 3)
			continue;

		struct ksym *new = alloc_ksym(addr, c2type(c_type), s_name,
				n == 4 ? s_kmod : NULL);
		if (!new)
			continue;

#ifdef DEBUG
		fprintf(stderr, "%d %lx %c %s %s\n", n, new->addr, c_type, new->name, new->kmod);
#endif

		struct ksym **old = tsearch(new, &ksyms.root_nkta, ksym_cmp_nkta);
		assert(old && "tsearch() failed");

		/* already exit */
		if (*old != new) {
			free_ksym(new);
			continue;
		}

		ksyms.nsyms++;

		old = tsearch(new, &ksyms.root_addr, ksym_cmp_addr);
		assert(old && "tsearch() failed");
	}

#ifdef DEBUG
	fprintf(stderr, "kallsyms %ld symbols\n", ksyms.nsyms);
#endif

	fclose(fp);
	return 0;
}
