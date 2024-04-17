#include <stdio.h>
#include <hugetlbfs.h>

int main(void)
{
	char *hugepage = NULL;

	hugepage = get_hugepage_region(gethugepagesize(), GHP_DEFAULT);

	printf("%p\n", hugepage);

	free_hugepage_region(hugepage);
	return 0;
}

