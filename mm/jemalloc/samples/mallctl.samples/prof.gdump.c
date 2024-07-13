#include <stdio.h>
#include <jemalloc/jemalloc.h>

//prof.gdump (bool) rw [--enable-prof]
//	When enabled, trigger a memory profile dump every time the total virtual memory exceeds the previous maximum.
//	Profiles are dumped to files named according to the pattern <prefix>.<pid>.<seq>.u<useq>.heap, where <prefix> is
//	controlled by the opt.prof_prefix and prof.dump_prefix options.


void set_jemalloc_prof_gdump(bool enable) {
	char val = !!enable;
	je_mallctl("prof.gdump", NULL, 0, &val, 1);
}
void get_jemalloc_prof_gdump(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("prof.gdump", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_prof_gdump(&enable);
	printf("enable = %d\n", enable);

	set_jemalloc_prof_gdump(enable);

	enable = false;
	get_jemalloc_prof_gdump(&enable);
	printf("enable = %d\n", enable);
}



