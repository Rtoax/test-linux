#include <stdio.h>
#include <jemalloc/jemalloc.h>
#include "swapper.h"

//opt.retain (bool) r-	保留
//	If true, retain unused virtual memory for later reuse rather than discarding it by calling munmap(2) or equivalent (
//	see stats.retained for related details). It also makes jemalloc use mmap(2) or equivalent in a more greedy way,
//	mapping larger chunks in one go. This option is disabled by default unless discarding virtual memory is known to
//	trigger platform-specific performance problems, namely 1) for [64-bit] Linux, which has a quirk in its virtual memory
//	allocation algorithm that causes semi-permanent VM map holes under normal jemalloc operation; and 2) for [64-bit]
//	Windows, which disallows split / merged regions with MEM_RELEASE. Although the same issues may present on 32-bit
//	platforms as well, retaining virtual memory for 32-bit Linux and Windows is disabled by default due to the practical
//	possibility of address space exhaustion.
//	为后面再次利用保留没用的虚拟内存，而不是忽略 使用munmap将其还给内核。

void get_jemalloc_opt_retain(bool *enable) {
	size_t size = sizeof(bool);
	je_mallctl("opt.retain", enable, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	bool enable = true;

	get_jemalloc_opt_retain(&enable);
	printf("enable = %d\n", enable);
}





