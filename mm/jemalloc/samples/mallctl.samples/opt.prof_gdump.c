#include <stdio.h>
#include <jemalloc/jemalloc.h>

//opt.prof_gdump (bool) r- [--enable-prof]
//	Set the initial state of prof.gdump, which when enabled triggers a memory profile dump every time the total virtual
//	memory exceeds the previous maximum. This option is disabled by default.

void get_jemalloc_opt_prof_gdump(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("opt.prof_gdump", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_opt_prof_gdump(&enable);
	printf("enable = %d\n", enable);
}

