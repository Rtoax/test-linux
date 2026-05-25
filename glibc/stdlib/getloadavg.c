#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int getloadavg_scale(int *l1, int *l5, int *l15, int scale)
{
	FILE *fp = fopen("/proc/loadavg", "r");
	if (!fp) {
		fprintf(stderr, "open /proc/loadavg failed, %m\n");
		return -errno;
	}

	float f1, f5, f15;
	fscanf(fp, "%f %f %f", &f1, &f5, &f15);

	*l1 = f1 * scale;
	*l5 = f5 * scale;
	*l15 = f15 * scale;

	fclose(fp);
	return 0;
}

int main(void)
{
	int i, ls[3];
	double loadavg[3];

	getloadavg(loadavg, 3);

	getloadavg_scale(&ls[0], &ls[1], &ls[2], 1000);

	for (i = 0; i < 3; i++) {
		printf("%d %lf %d\n", i, loadavg[i], ls[i]);
	}
	return 0;
}
