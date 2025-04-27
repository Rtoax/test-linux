#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <linux/mempolicy.h>
#include <numaif.h>
#include "numa_helpers.h"

void print_mpol(int mpol)
{
	switch (mpol) {
#define CASE(v) case v: printf("%s(%d)\n", #v, v); break
	CASE(MPOL_DEFAULT);
	CASE(MPOL_PREFERRED);
	CASE(MPOL_BIND);
	CASE(MPOL_INTERLEAVE);
	CASE(MPOL_LOCAL);
#if defined(MPOL_PREFERRED_MANY)
	CASE(MPOL_PREFERRED_MANY);
#endif
#if defined(MPOL_WEIGHTED_INTERLEAVE)
	CASE(MPOL_WEIGHTED_INTERLEAVE);
#endif
#undef CASE
	default: printf("Unknown\n"); break;
	}
}

void print_mpol_f(int mpol_f)
{
	switch (mpol_f) {
#define CASE(v) case v: printf("%s(%d)\n", #v, v); break
	/* Flags for set_mempolicy */
	CASE(MPOL_F_STATIC_NODES);
	CASE(MPOL_F_RELATIVE_NODES);
#if defined(MPOL_F_NUMA_BALANCING)
	CASE(MPOL_F_NUMA_BALANCING);
#endif
	/* Flags for get_mempolicy */
	CASE(MPOL_F_NODE);
	CASE(MPOL_F_ADDR);
	CASE(MPOL_F_MEMS_ALLOWED);
# if 0 /* see /usr/include/linux/mempolicy.h */
	CASE(MPOL_F_SHARED);
	CASE(MPOL_F_MOF);
	CASE(MPOL_F_MORON);
# endif
#undef CASE
	default: printf("Unknown\n"); break;
	}
}

int print_nodemask(const char *pfx, unsigned long *nodemask,
		   unsigned long maxnode)
{
	int nr_nodes, i;
	char *str;

	str = malloc(maxnode + 1);
	memset(str, 0x00, maxnode + 1);
	nr_nodes = 0;

	for (i = 0; i < maxnode; i++)
		if (nodemask[i / sizeof(unsigned long)] & (1UL << (i % 8))) {
			str[i] = '1';
			nr_nodes++;
		} else
			str[i] = '0';

	printf("%s%s\n", pfx ?: "", str);

	free(str);
	return nr_nodes;
}

int get_addr_node(void *vaddr)
{
	int ret, flags, mode;
	flags = MPOL_F_NODE | MPOL_F_ADDR;
	ret = get_mempolicy(&mode, NULL, 0, (void *)vaddr, flags);
	if (ret != 0)
		perror("get_mempolicy");
	return mode;
}

