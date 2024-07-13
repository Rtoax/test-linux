#include <stdio.h>
#include <jemalloc/jemalloc.h>

//opt.muzzy_decay_ms (ssize_t) r-	模糊，混乱页清除时延
//	Approximate time in milliseconds from the creation of a set of unused muzzy(模糊，混乱) pages until an equivalent set of unused
//	muzzy pages is purged (i.e. converted to clean) and/or reused. Muzzy pages are defined as previously having been
//	unused dirty pages that were subsequently purged in a manner that left them subject to the reclamation whims of the
//	operating system (e.g. madvise(...MADV_FREE)), and therefore in an indeterminate state. The pages are incrementally
//	purged according to a sigmoidal decay curve that starts and ends with zero purge rate. A decay time of 0 causes all
//	unused muzzy pages to be purged immediately upon creation. A decay time of -1 disables purging. The default decay
//	time is 10 seconds. See arenas.muzzy_decay_ms and arena.<i>.muzzy_decay_ms for related dynamic control options.

void get_jemalloc_opt_muzzy_decay_ms(ssize_t *value) {
	ssize_t size = sizeof(ssize_t);
	je_mallctl("opt.muzzy_decay_ms", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	ssize_t value = 0;

	get_jemalloc_opt_muzzy_decay_ms(&value);
	printf("value = %ld milliseconds\n", value);
}




