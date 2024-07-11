#include <stdio.h>

void print_time(char *label, long time)
{
	/* Conversion constants. */
	const long minute = 60;
	const long hour = minute * 60;
	const long day = hour * 24;
	/* Produce output. */
	printf("%s: %ld days, %ld:%02ld:%02ld\n", label, time / day,
		(time % day) / hour,(time % hour) / minute, time % minute);
}

int main(void)
{
	FILE *fp;
	double uptime, idle_time;

	fp = fopen("/proc/uptime", "r");
	fscanf(fp, "%lf %lf\n", &uptime, &idle_time);
	fclose(fp);

	/* Summarize it. */
	print_time("uptime ", (long)uptime);
	print_time("idle time", (long)idle_time);

	return 0;
}
