/* SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause) */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>

int main(void)
{
	int n, err = 0;
	char avg[64];
	FILE *f;
	int nloop = 4;

	f = fopen("/proc/loadavg", "r");
	if (!f) {
		perror("fopen(/proc/loadavg)");
		return -1;
	}

	while (nloop--) {
		memset(avg, 0, sizeof(avg));
		n = fread(avg, 1, sizeof(avg), f);
		if (n <= 1 || ftell(f) != n) {
			err = -1;
			goto cleanup;
		}
		rewind(f);

		printf("loadavg: %s", avg);
		usleep(10000);
	}

cleanup:
	fclose(f);
	return err;
}
