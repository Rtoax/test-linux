#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int i;
	FILE *fp;
	unsigned int ios_pgr, tot_ticks, rq_ticks, wr_ticks, dc_ticks, fl_ticks;
	unsigned long rd_ios, rd_merges_or_rd_sec, wr_ios, wr_merges;
	unsigned long rd_sec_or_wr_ios, wr_sec, rd_ticks_or_wr_sec;
	unsigned long dc_ios, dc_merges, dc_sec, fl_ios;

	fp = fopen("/sys/block/sda/stat", "r");
	if (fp == NULL) {
		fprintf(stderr, "fopen %m\n");
		exit(1);
	}

	i = fscanf(fp, "%lu %lu %lu %lu %lu %lu %lu %u %u %u %u %lu %lu %lu %u %lu %u",
		   &rd_ios, &rd_merges_or_rd_sec, &rd_sec_or_wr_ios, &rd_ticks_or_wr_sec,
		   &wr_ios, &wr_merges, &wr_sec, &wr_ticks, &ios_pgr, &tot_ticks, &rq_ticks,
		   &dc_ios, &dc_merges, &dc_sec, &dc_ticks,
		   &fl_ios, &fl_ticks);

	printf("i = %d\n", i);

	if (i != 17) {
		fprintf(stderr, "ERROR: bad sysfs version\n");
	}

	return 0;
}
