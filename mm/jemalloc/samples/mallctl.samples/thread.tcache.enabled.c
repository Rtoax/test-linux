#include <stdio.h>
#include <jemalloc/jemalloc.h>

//thread.tcache.enabled (bool) rw
//	Enable/disable calling thread's tcache. The tcache is implicitly flushed as a side effect of becoming disabled (see
//	thread.tcache.flush).


void set_jemalloc_thread_tcache_enabled(bool enable)
{
	char val = !!enable;
	je_mallctl("thread.tcache.enabled", NULL, 0, &val, 1);
}
void get_jemalloc_thread_tcache_enabled(bool *enable)
{
	size_t size = sizeof(bool);
	je_mallctl("thread.tcache.enabled", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_thread_tcache_enabled(&enable);
	printf("enable = %d\n", enable);

	set_jemalloc_thread_tcache_enabled(enable);
	printf("enable = %d\n", enable);
}

