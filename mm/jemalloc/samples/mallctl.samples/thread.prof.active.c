#include <stdio.h>
#include <jemalloc/jemalloc.h>

//thread.prof.active (bool) rw [--enable-prof]
//	Control whether sampling is currently active for the calling thread. This is an activation mechanism in addition to
//	prof.active; both must be active for the calling thread to sample. This flag is enabled by default.


void set_jemalloc_thread_perf_active(bool enable)
{
	char val = !!enable;
	je_mallctl("thread.prof.active", NULL, 0, &val, 1);
}
void get_jemalloc_thread_perf_active(bool *enable)
{
	size_t size = sizeof(bool);
	je_mallctl("thread.prof.active", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_thread_perf_active(&enable);
	printf("enable = %d\n", enable);

	set_jemalloc_thread_perf_active(enable);
	printf("enable = %d\n", enable);
}


