#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <stdio.h>

#include <mlinklist.h>
#include <common.h>


void create_mll(mll_t *mll, const char *file, size_t size, int write)
{
	int flag;

	mll->size = size;

	strncpy(mll->filename, file, sizeof(mll->filename));

	if (write) {
		flag = O_RDWR|O_CREAT|O_TRUNC;
	} else {
		flag = O_RDWR;
	}

	mll->fd = open(file, flag, 0644);
	if (mll->fd == -1) {
		perror("open\n");
		exit(1);
	}

	if ((ftruncate(mll->fd, mll->size)) == -1) {
		perror("ftruncate\n");
		exit(1);
	}

	mll->addr = mmap(NULL, mll->size, PROT_WRITE|PROT_READ, MAP_SHARED, mll->fd, 0);
	if (mll->addr == MAP_FAILED) {
		perror("mmap\n");
		exit(1);
	}

	mll->hdr = (struct mll_hdr*)mll->addr;

	if (write) {
		mll->hdr->curr_off = sizeof(struct mll_hdr);
	}
}

void mll_insert(mll_t *mll, struct ll_node *node)
{
	struct ll_node *_node = (struct ll_node *)(mll->addr + mll->hdr->curr_off);

	_node->i = node->i;

	if (mll->hdr->curr_off > sizeof(struct mll_hdr)) {
		struct ll_node *_prev = (struct ll_node *)(mll->addr
					     + mll->hdr->curr_off
					     - sizeof(struct ll_node));
		_prev->offset = mll->hdr->curr_off;
	}
	_node->next = NULL;

	mll->hdr->curr_off += sizeof(struct ll_node);
}

void mll_foreach(mll_t *mll, void (*foreach)(struct ll_node *node))
{
	if (mll->hdr->curr_off <= sizeof(struct mll_hdr)) {
		return;
	}

	struct ll_node *_node = (struct ll_node *)(mll->addr + sizeof(struct mll_hdr));

	do {
		foreach(_node);

		if(!_node->next) break;

		_node = (struct ll_node *)(mll->addr + _node->offset);
	} while(_node);
}
