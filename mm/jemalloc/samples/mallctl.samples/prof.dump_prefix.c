#include <stdio.h>
#include <jemalloc/jemalloc.h>

//prof.dump_prefix (const char *) -w [--enable-prof]
//	Set the filename prefix for profile dumps. See opt.prof_prefix for the default setting. This can be useful to
//	differentiate profile dumps such as from forked processes.


void set_jemalloc_prof_dump_prefix(const char* value) {
	je_mallctl("prof.dump_prefix", NULL, 0, &value, 32);
}
//void get_jemalloc_prof_dump_prefix(bool *enable) {
//	je_mallctl("prof.dump_prefix", enable, &size, NULL, 0);
//}

int main(int argc,char **argv)
{
	set_jemalloc_prof_dump_prefix("coredump");
}

//TODO: coredump文件如何生成，看下测试例


