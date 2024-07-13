#include <stdio.h>
#include <jemalloc/jemalloc.h>

//prof.active (bool) rw [--enable-prof]
//	Control whether sampling is currently active. See the opt.prof_active option for additional information, as well as
//	the interrelated thread.prof.active mallctl.


void set_jemalloc_prof_active(bool enable) {
	char val = !!enable;
	je_mallctl("prof.active", NULL, 0, &val, 1);
}
void get_jemalloc_prof_active(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("prof.active", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_prof_active(&enable);
	printf("enable = %d\n", enable);

	set_jemalloc_prof_active(enable);

	enable = false;
	get_jemalloc_prof_active(&enable);
	printf("enable = %d\n", enable);
}


