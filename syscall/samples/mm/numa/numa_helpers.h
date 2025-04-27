#pragma once

#ifndef MPOL_LOCAL
#define MPOL_LOCAL	4
#endif

void print_mpol(int mpol);
void print_mpol_f(int mpol_f);
int print_nodemask(const char *pfx, unsigned long *nodemask,
		   unsigned long maxnode);

int get_addr_node(void *vaddr);
