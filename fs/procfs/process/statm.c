#include <stdlib.h>
#include <stdio.h>

/**
 * /proc/[pid]/statm
 *
 * Provides information about memory usage, measured in pages.
 * The columns are:
 *
 * size       total program size
 *            (same as VmSize in /proc/[pid]/status)
 * resident   resident set size
 *            (same as VmRSS in /proc/[pid]/status)
 * share      shared pages (from shared mappings)
 * text       text (code)
 * lib        library (unused in Linux 2.6)
 * data       data + stack
 * dt         dirty pages (unused in Linux 2.6)
 */
typedef struct {
	unsigned long size, resident, share, text, lib, data, dt;
} statm_t;

void read_off_memory_status(statm_t *result)
{
	const char *statm_path = "/proc/self/statm";

	FILE *f = fopen(statm_path,"r");
	if(!f){
		perror(statm_path);
		abort();
	}
	if(7 != fscanf(f,"%lu %lu %lu %lu %lu %lu %lu",
			&result->size,
			&result->resident,
			&result->share,
			&result->text,
			&result->lib,
			&result->data,
			&result->dt)) {
		perror(statm_path);
		abort();
	}
	fclose(f);
}

int main(void)
{
	statm_t statm;
	read_off_memory_status(&statm);
	return 0;
}
