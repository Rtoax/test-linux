#include <stdio.h>
#include <jemalloc/jemalloc.h>

//prof.thread_active_init (bool) rw [--enable-prof]
//	Control the initial setting for thread.prof.active in newly created threads. See the opt.prof_thread_active_init
//	option for additional information.
// See also: thread.prof.active (bool) rw [--enable-prof]


void set_jemalloc_prof_thread_active_init(bool enable) {
	char val = !!enable;
	je_mallctl("prof.thread_active_init", NULL, 0, &val, 1);
}
void get_jemalloc_prof_thread_active_init(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("prof.thread_active_init", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_prof_thread_active_init(&enable);
	printf("enable = %d\n", enable);

	set_jemalloc_prof_thread_active_init(enable);

	enable = false;
	get_jemalloc_prof_thread_active_init(&enable);
	printf("enable = %d\n", enable);
}

