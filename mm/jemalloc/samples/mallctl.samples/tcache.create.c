#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//tcache.create (unsigned) r-
//	Create an explicit thread-specific cache (tcache) and return an identifier that can be passed to the MALLOCX_TCACHE(tc
//	) macro to explicitly use the specified cache rather than the automatically managed one that is used by default. Each
//	explicit cache can be used by only one thread at a time; the application must assure that this constraint holds.
//	创建一个明确的线程特有的cache，并且返回一个标识，这个标识被传输 MALLOCX_TCACHE
//	宏定义传输至特定的cache，否则自动管理一个默认的。
//	每个特定的cache在同一时刻只可以被一个线程使用；应用必须确认满足这个约束条件。

//	If the amount of space supplied for storing the thread-specific cache identifier does not equal sizeof(unsigned), no
//	thread-specific cache will be created, no data will be written to the space pointed by oldp, and *oldlenp will be set
//	to 0.
//	如果大小不等于 sizeof(unsigned) ，那么没有cache被创建，

void get_jemalloc_tcache_create(unsigned *value)
{
	size_t size = sizeof(unsigned);
	je_mallctl("tcache.create", value, &size, NULL, 0);
}
void jemalloc_tcache_flush()
{
	je_mallctl("tcache.flush", NULL, NULL, NULL, 0);
}



int main(int argc,char **argv)
{
	unsigned value = 1;

	get_jemalloc_tcache_create(&value);
	printf("value = %d\n", value);

	char *str = je_malloc(1025);

	get_jemalloc_tcache_create(&value);
	printf("value = %d\n", value);

	je_free(str);

	get_jemalloc_tcache_create(&value);
	printf("value = %d\n", value);

	jemalloc_tcache_flush();
	je_free(str);

	get_jemalloc_tcache_create(&value);
	printf("value = %d\n", value);

	jemalloc_tcache_flush();

	get_jemalloc_tcache_create(&value);
	printf("value = %d\n", value);

}



