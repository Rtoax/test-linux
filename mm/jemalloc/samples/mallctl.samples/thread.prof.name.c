#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//thread.prof.name (const char *) r- or -w [--enable-prof]
//	Get/set the descriptive name associated with the calling thread in memory profile dumps. An internal copy of the name
//	string is created, so the input string need not be maintained after this interface completes execution. The output
//	string of this interface should be copied for non-ephemeral uses, because multiple implementation details can cause
//	asynchronous string deallocation. Furthermore, each invocation of this interface can only read or write; simultaneous
//	read/write is not supported due to string lifetime limitations. The name string must be nil-terminated and comprised
//	only of characters in the sets recognized by isgraph(3) and isblank(3).

void get_jemalloc_thread_prof_name(char *value) {
	size_t size = 32;
	je_mallctl("thread.prof.name", value, &size, NULL, 0);
}

void set_jemalloc_thread_prof_name(char *value, size_t len) {
	je_mallctl("thread.prof.name", NULL, NULL, value, len);
}


int main(int argc,char **argv)
{
	char value[256] = {"123"};

	get_jemalloc_thread_prof_name(value);
	printf("value = %s\n", value);

	set_jemalloc_thread_prof_name("RTOAX", 5);
	get_jemalloc_thread_prof_name(value);
	printf("value = %s\n", value);

}


