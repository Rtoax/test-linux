#include <stdio.h>
#include <hugetlbfs.h>

int main(void)
{
	char *hugepage = NULL;

	hugepage = get_huge_pages(gethugepagesize(), GHP_DEFAULT);
	printf("%p\n", hugepage);
	free_huge_pages(hugepage);

	return 0;
}
