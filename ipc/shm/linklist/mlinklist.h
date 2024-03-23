#ifndef __MML_H
#define __MML_H 1

#include <sys/types.h>
#include <common.h>

struct mll_hdr {
	size_t curr_off;
};

typedef struct mlinklist_s {
	char filename[32];
	int fd;
	size_t size;
	char *addr;
	struct mll_hdr *hdr;
} mll_t;

void create_mll(mll_t *mll, const char *file, size_t size, int write);
void mll_insert(mll_t *mll, struct ll_node *node);
void mll_foreach(mll_t *mll, void (*foreach)(struct ll_node *node));

#endif //__MML_H
