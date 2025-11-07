#define GPERFTOOLS_HAS_MALLINFO	1
#include <gperftools/tcmalloc.h>
#include <stdio.h>

void print_mallinfo(struct mallinfo *info)
{
	struct mallinfo *mf1 = info;
	printf("mallinfo.arena		= %d.\n", mf1->arena);
	printf("mallinfo.ordblks	= %d.\n", mf1->ordblks);
	printf("mallinfo.smblks		= %d.\n", mf1->smblks);
	printf("mallinfo.hblks		= %d.\n", mf1->hblks);
	printf("mallinfo.hblkhd		= %d.\n", mf1->hblkhd);
	printf("mallinfo.usmblks	= %d.\n", mf1->usmblks);
	printf("mallinfo.fsmblks	= %d.\n", mf1->fsmblks);
	printf("mallinfo.uordblks	= %d.\n", mf1->uordblks);
	printf("mallinfo.fordblks	= %d.\n", mf1->fordblks);
	printf("mallinfo.keepcost	= %d.\n", mf1->keepcost);
}

int main(void)
{
	struct mallinfo info = tc_mallinfo();
	print_mallinfo(&info);

	char *str = tc_pvalloc(1024 * 1024 * 1024);
	printf("%s\n", str);

	info = tc_mallinfo();

	print_mallinfo(&info);

	tc_free(str);

	info = tc_mallinfo();
	print_mallinfo(&info);
}
