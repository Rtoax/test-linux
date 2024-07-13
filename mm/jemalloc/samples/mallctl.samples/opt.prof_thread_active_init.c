#include <stdio.h>
#include <jemalloc/jemalloc.h>

//opt.prof_thread_active_init (bool) r- [--enable-prof]
//	Initial setting for thread.prof.active in newly created threads. The initial setting for newly created threads can
//	also be changed during execution via the prof.thread_active_init mallctl. This option is enabled by default.


void get_jemalloc_opt_prof_thread_active_init(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("opt.prof_thread_active_init", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_opt_prof_thread_active_init(&enable);
	printf("enable = %d\n", enable);
}
