#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

static const char *stats[] = {
	"/sys/block/sda/stat",
	"/sys/block/vda/stat",
	"/sys/block/nvme0n1/stat",
};

int main(void)
{
	int n, err = 0;
	FILE *fp = NULL;
	unsigned int ios_pgr, tot_ticks, rq_ticks, wr_ticks, dc_ticks, fl_ticks;
	unsigned long rd_ios, rd_merges_or_rd_sec, wr_ios, wr_merges;
	unsigned long rd_sec_or_wr_ios, wr_sec, rd_ticks_or_wr_sec;
	unsigned long dc_ios, dc_merges, dc_sec, fl_ios;

	for (int i = 0; i < sizeof(stats) / sizeof(stats[0]); i++) {
		fp = fopen(stats[i], "r");
		if (fp == NULL) {
			fprintf(stderr, "fopen %s %m\n", stats[i]);
			continue;
		}
		if (fp)
			break;
	}

	if (!fp)
		exit(EXIT_FAILURE);

	n = fscanf(
		fp,
		"%lu %lu %lu %lu %lu %lu %lu %u %u %u %u %lu %lu %lu %u %lu %u",
		&rd_ios, &rd_merges_or_rd_sec, &rd_sec_or_wr_ios,
		&rd_ticks_or_wr_sec, &wr_ios, &wr_merges, &wr_sec, &wr_ticks,
		&ios_pgr, &tot_ticks, &rq_ticks, &dc_ios, &dc_merges, &dc_sec,
		&dc_ticks, &fl_ios, &fl_ticks);

	printf("n = %d\n", n);

	if (n != 17) {
		fprintf(stderr, "ERROR: bad sysfs version\n");
		err = -EINVAL;
	}

	fclose(fp);
	return err;
}
