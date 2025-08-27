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
#define DEFAULT_KMOD	"vmlinux"


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

struct ksyms_tree {
	size_t nsyms;
	void *root;
	int (*compare)(const void *, const void *);
	void (*walk)(const void *, VISIT, void *);
};

struct ksyms_array {
	struct ksym *array;
	size_t nsyms, cap;
};

struct ksyms {
	struct ksyms_tree nkta, name, addr;
	struct ksyms_array arr_addr;
};

void print_ksym(const struct ksym *sym);

static int ksym_cmp_addr(const void *a1, const void *a2)
{
	const struct ksym *s1 = a1, *s2 = a2;
	return s1->addr - s2->addr;
}

static int ksym_cmp_name(const void *a1, const void *a2)
{
	const struct ksym *s1 = a1, *s2 = a2;
	return strcmp(s1->name, s2->name);
}

static int ksym_cmp_nkta(const void *a1, const void *a2)
{
	int cmp;
	const struct ksym *s1 = a1, *s2 = a2;

	cmp = strcmp(s1->name, s2->name);
	if (cmp)
		return cmp;
	cmp = strcmp(s1->kmod, s2->kmod);
	if (cmp)
		return cmp;
	cmp = s1->type - s2->type;
	if (cmp)
		return cmp;
	return ksym_cmp_addr(s1, s2);
}

void walk_action(const void *nodep, VISIT which, void *closure)
{
	const struct ksym *sym = *(struct ksym **)nodep;

	if (which != preorder && which != leaf)
		return;

	print_ksym(sym);
}

static const struct ksyms default_zero_ksyms = {
	.nkta = {
		.nsyms = 0,
		.root = NULL,
		.compare = ksym_cmp_nkta,
		.walk = walk_action,
	},
	.name = {
		.nsyms = 0,
		.root = NULL,
		.compare = ksym_cmp_name,
		.walk = walk_action,
	},
	.addr = {
		.nsyms = 0,
		.root = NULL,
		.compare = ksym_cmp_addr,
		.walk = walk_action,
	},
};


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
	char module[64];
	struct ksym *new;

	if (addr == 0 || !name || strlen(name) <= 1)
		return NULL;
	if (!kmod)
		kmod = DEFAULT_KMOD;

	strcpy(module, kmod);
	kmod = module;
	if (kmod[0] == '[') {
		kmod++;
		kmod[strlen(kmod) - 1] = '\0';
	}

	new = malloc(sizeof(struct ksym));

	memset(new, 0, sizeof(struct ksym));
	new->addr = addr;
	new->type = type;
	new->name = strdup(name);
	new->kmod = strdup(kmod);

	return new;
}

struct ksym *dup_ksym(struct ksym *old)
{
	return alloc_ksym(old->addr, old->type, old->name, old->kmod);
}

void print_ksym(const struct ksym *sym)
{
	fprintf(stderr, "%lx %c %s %s\n", sym->addr, type2c(sym->type),
		sym->name, sym->kmod ?: "");
}

void free_ksym(struct ksym *ksym)
{
	if (!ksym)
		return;
	free(ksym->name);
	if (ksym->kmod)
		free(ksym->kmod);
	free(ksym);
}

static void free_ksym_t(void *p)
{
	free_ksym(p);
}

int insert_to_tree(struct ksyms_tree *tree, struct ksym *new)
{
	struct ksym *dup, **old;

	dup = dup_ksym(new);
	if (!dup)
		return -1;

	old = tsearch(dup, &tree->root, tree->compare);
	assert(old && "tsearch() failed");

	if (*old != dup) {
		free_ksym(dup);
		return -1;
	}
	tree->nsyms++;
	return 0;
}

int insert_to_array(struct ksyms_array *arr, struct ksym *new)
{
	size_t new_cap;
	struct ksym *dup;

	dup = dup_ksym(new);
	if (!dup)
		return -1;

	if (arr->nsyms + 1 > arr->cap) {
		new_cap = arr->cap * 4 / 3;
		if (new_cap < 1024)
			new_cap = 1024;
		arr->array = realloc(arr->array, sizeof(struct ksym) * new_cap);
		if (!arr->array)
			return -1;
		arr->cap = new_cap;
	}

	memcpy(&arr->array[arr->nsyms], dup, sizeof(struct ksym));
	arr->nsyms++;

	return 0;
}

int sort_array(struct ksyms_array *arr)
{
	qsort(arr->array, arr->nsyms, sizeof(struct ksym), ksym_cmp_addr);
	return 0;
}

void walk_tree(struct ksyms_tree *tree)
{
	twalk_r(tree->root, tree->walk, NULL);
}

struct ksyms *load_kallsyms(void)
{
	int n;
	FILE *fp;
	unsigned long addr;
	char c_type, s_name[256], s_kmod[128];
	char line[512];
	struct ksyms *ksyms;

	fp = fopen(PROC_KALLSYMS, "r");
	if (!fp)
		return NULL;

	ksyms = malloc(sizeof(struct ksyms));
	if (!ksyms)
		goto exit;

	memset(ksyms, 0, sizeof(struct ksyms));
	memcpy(ksyms, &default_zero_ksyms, sizeof(struct ksyms));

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

		insert_to_array(&ksyms->arr_addr, new);
		insert_to_tree(&ksyms->nkta, new);
		insert_to_tree(&ksyms->name, new);
		insert_to_tree(&ksyms->addr, new);

		free_ksym(new);
	}

	sort_array(&ksyms->arr_addr);

#ifdef DEBUG
	fprintf(stderr, "kallsyms nkta %ld, name %ld, addr %ld symbols\n",
		ksyms->nkta.nsyms, ksyms->name.nsyms, ksyms->addr.nsyms);
# if DEBUG >= 2
	walk_tree(&ksyms->nkta);
	walk_tree(&ksyms->name);
	walk_tree(&ksyms->addr);
# endif
#endif

exit:
	fclose(fp);
	return ksyms;
}

void free_kallsyms(struct ksyms *ksyms)
{
	tdestroy(ksyms->nkta.root, free_ksym_t);
	tdestroy(ksyms->name.root, free_ksym_t);
	tdestroy(ksyms->addr.root, free_ksym_t);
	free(ksyms->arr_addr.array);
}

long ksym_addr(const struct ksyms *ksyms, const char *name)
{
	struct ksym **found, find;

	if (!ksyms || !name)
		return -EINVAL;

	memset(&find, 0, sizeof(struct ksym));

	find.name = (char *)name;

	found = tfind(&find, &ksyms->name.root, ksyms->name.compare);
	if (found)
		return (*found)->addr;

	return INVALID_ADDR;
}

const char *ksym_name(const struct ksyms *ksyms, unsigned long address,
		      unsigned long *off)
{
	int start = 0, end = ksyms->arr_addr.nsyms - 1, mid;
	unsigned long addr;

	if (!ksyms)
		return NULL;

	while (start < end) {
		mid = start + (end - start + 1) / 2;
		addr = ksyms->arr_addr.array[mid].addr;
		if (addr <= address)
			start = mid;
		else
			end = mid - 1;
	}
	if (start == end && ksyms->arr_addr.array[start].addr <= address) {
		if (off) {
			addr = ksyms->arr_addr.array[start].addr;
			*off = address - addr;
		}
		return ksyms->arr_addr.array[start].name;
	}
	return NULL;
}
