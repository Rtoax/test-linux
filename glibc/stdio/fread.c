/* SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>


int main(void)
{
	int n, err = 0;
	char avg[64];
	FILE *f;

	f = fopen("/proc/loadavg", "r");
	if (!f) {
		perror("fopen(/proc/loadavg)");
		return -1;
	}

	n = fread(avg, 1, sizeof(avg), f);
	if (n <= 1) {
		err = -1;
		goto cleanup;
	}

	printf("loadavg: %s", avg);

cleanup:
	fclose(f);
	return err;
}
