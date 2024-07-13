#include <stdio.h>
#include <jemalloc/jemalloc.h>

//prof.reset (size_t) -w [--enable-prof]
//	Reset all memory profile statistics, and optionally update the sample rate (see opt.lg_prof_sample and prof.lg_sample).


void set_jemalloc_prof_reset(size_t value) {
	je_mallctl("prof.reset", NULL, 0, &value, sizeof(size_t));
}
//void get_jemalloc_prof_reset(bool *enable) {
//	je_mallctl("prof.reset", enable, &size, NULL, 0);
//}

int main(int argc,char **argv)
{
	set_jemalloc_prof_reset(1);
}

//TODO: coredump文件如何生成，看下测试例


