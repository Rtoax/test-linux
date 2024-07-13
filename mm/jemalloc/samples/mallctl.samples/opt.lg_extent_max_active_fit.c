#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//opt.lg_extent_max_active_fit (size_t) r-	当重新利用脏页，这个数值决定最大的比值（被选中的激活范围 和 请求分配的 比值）
//	When reusing dirty extents, this determines the (log base 2 of the) maximum ratio between the size of the active
//	extent(范围) selected (to split off from) and the size of the requested allocation. This prevents the splitting of large
//	active extents(范围) for smaller allocations, which can reduce fragmentation over the long run (especially for non-active
//	extents(范围)). Lower value may reduce fragmentation, at the cost of extra active extents. The default value is 6, which
//	gives a maximum ratio of 64 (2^6).
//	当重新利用脏页，这个数值决定最大的比值（被选中的激活范围 和 请求分配的 比值）

void get_jemalloc_opt_lg_extent_max_active_fit(size_t *value) {
	size_t size = 4;
	je_mallctl("opt.lg_extent_max_active_fit", value, &size, NULL, 0);
}


int main(int argc,char **argv)
{
	size_t value = 0;

	get_jemalloc_opt_lg_extent_max_active_fit(&value);
	printf("value = %ld\n", value);
}



