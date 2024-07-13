#include <stdio.h>
#include <jemalloc/jemalloc.h>

//opt.dirty_decay_ms (ssize_t) r- 脏页清除时延
//	Approximate time in milliseconds from the creation of a set of unused dirty pages until an equivalent set of unused
//	dirty pages is purged (i.e. converted to muzzy via e.g. madvise(...MADV_FREE) if supported by the operating system,
//	or converted to clean otherwise) and/or reused. Dirty pages are defined as previously having been potentially written
//	to by the application, and therefore consuming physical memory, yet having no current use. The pages are
//	incrementally purged according to a sigmoidal decay curve that starts and ends with zero purge rate. A decay time of
//	0 causes all unused dirty pages to be purged immediately upon creation. A decay time of -1 disables purging. The
//	default decay time is 10 seconds. See arenas.dirty_decay_ms and arena.<i>.dirty_decay_ms for related dynamic control
//	options. See opt.muzzy_decay_ms for a description of muzzy pages.for a description of muzzy pages. Note that when the
//	oversize_threshold feature is enabled, the arenas reserved for oversize requests may have its own default decay
//	settings.

void get_jemalloc_opt_dirty_decay_ms(ssize_t *value) {
	ssize_t size = sizeof(ssize_t);
	je_mallctl("opt.dirty_decay_ms", value, &size, NULL, 0);
}

int main(int argc,char **argv)
{
	ssize_t value = 0;

	get_jemalloc_opt_dirty_decay_ms(&value);
	printf("value = %ld milliseconds\n", value);
}



