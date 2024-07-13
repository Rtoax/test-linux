#include <stdio.h>
#include <jemalloc/jemalloc.h>

//prof.dump (const char *) -w [--enable-prof]
//	Dump a memory profile to the specified file, or if NULL is specified, to a file according to the pattern <prefix>.<pid
//	>.<seq>.m<mseq>.heap, where <prefix> is controlled by the opt.prof_prefix and prof.dump_prefix options.


void set_jemalloc_prof_dump(const char* value) {
	je_mallctl("prof.dump", NULL, 0, &value, 32);
}
//void get_jemalloc_prof_dump(bool *enable) {
//	je_mallctl("prof.dump", enable, &size, NULL, 0);
//}

int main(int argc,char **argv)
{
	set_jemalloc_prof_dump("coredump");
}

//TODO: coredump文件如何生成，看下测试例

