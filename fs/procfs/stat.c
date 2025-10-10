#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


int main(void)
{
	long double a[4], b[4], loadavg;
	FILE *fp;

	for (;;) {
		fp = fopen("/proc/stat","r");
		fscanf(fp, "%*s %Lf %Lf %Lf %Lf", &a[0], &a[1], &a[2], &a[3]);
		fclose(fp);

		sleep(2);

		fp = fopen("/proc/stat","r");
		fscanf(fp, "%*s %Lf %Lf %Lf %Lf", &b[0], &b[1], &b[2], &b[3]);
		fclose(fp);

		/**
		 * user, nice, system, idle, iowait, irq, softirq, steal, guest, guest_nice.
		 *
		 * Example:
		 * cpu  195044598 6619 410450970 967314001 64039 0 85058 394458 0 0
		 * cpu0 48705507 1701 102480874 241499274 14130 0 82302 103069 0 0
		 */

		/**
		 * (user + nice + system)/(user + nice + system + idle + iowait + irq + softirq) * 100%
		 */
		loadavg = ((b[0] + b[1] + b[2]) - (a[0] + a[1] + a[2])) / \
			((b[0] + b[1] + b[2] + b[3]) - (a[0] + a[1] + a[2] + a[3]));
		printf("The total CPU utilization is %Lf%%\n", loadavg * 100.0);
	}

	return(0);
}
