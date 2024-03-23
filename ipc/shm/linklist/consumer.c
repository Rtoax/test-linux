#include <stdio.h>

#include <mlinklist.h>
#include <common.h>


void foreach(struct ll_node *node)
{
	printf("foreach: %d %ld.\n", node->i, node->offset);
}

int main(void)
{
	mll_t mll;

	create_mll(&mll, MMAP_FILENAME, sizeof(struct ll_node) * LINKLIST_SIZE, 0);

	mll_foreach(&mll, foreach);

	return 0;
}
