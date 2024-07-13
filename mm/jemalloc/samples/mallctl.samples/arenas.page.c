#include <stdio.h>
#include <jemalloc/jemalloc.h>

//arenas.page (size_t) r-
//	Page size.


void jemalloc_arena_page()
{
	size_t page;
		int i;
	size_t mib[3];
	size_t len, miblen;

	len = sizeof(page);
	je_mallctl("arenas.page", &page, &len, NULL, 0);
	printf("page = %ld.\n", page);

}

int main()
{
	printf("MALLCTL_ARENAS_ALL = %ld\n", MALLCTL_ARENAS_ALL);
	jemalloc_arena_page();
}



