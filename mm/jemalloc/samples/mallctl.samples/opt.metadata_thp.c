#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//opt.metadata_thp (const char *) r-
//	Controls whether to allow jemalloc to use transparent huge page (THP) for internal metadata (see stats.metadata).
//	“always” allows such usage. “auto” uses no THP initially, but may begin to do so when metadata usage reaches
//	certain level. The default is “disabled”.
//	是否可以使用 transparent hugepage（THP）在内部元数据中。
//	当其为 “always”时，允许使用
//	当其为 “auto”时，初始化时期没有THP，后续当元数据用到中期水平后，将使用大页内存


void get_jemalloc_opt_metadata_thp(char *value) {
	size_t size = 256;
	je_mallctl("opt.metadata_thp", value, &size, NULL, 0);
}


int main(int argc,char **argv)
{
	char value[256] = {"123"};

	get_jemalloc_opt_metadata_thp(value);
	printf("value = %s\n", value);
}
