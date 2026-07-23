#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/sysinfo.h>
#include <string.h>

typedef struct sysinfo Sys;

char* humanTime(long time)
{
	const long MIN_S = 60;
	const long HOUR_S = MIN_S * 60;
	const long DAY_S = HOUR_S * 24;
	const long WEEK_S = DAY_S * 7;

	long weeks = time / WEEK_S;
	time -= weeks * WEEK_S;

	long days = time / DAY_S;
	time -= days * DAY_S;

	long hours = time / HOUR_S;
	time -= hours * HOUR_S;

	long mins = time / MIN_S;
	time -= mins * MIN_S;

	size_t str_len = 255;
	char *str = malloc(str_len);

	snprintf(
		str, str_len,
		"Up %ld weeks, %ld days, %ld hours, %ld minutes, and %ld seconds",
		weeks, days, hours, mins, time);

	return str;
}

int main(void)
{
	Sys info = { 0 };
	sysinfo(&info);

	/* Get boot time */
	const time_t boot = time(NULL) - ((time_t) info.uptime);
	struct tm *boot_tm = localtime(&boot);

	char boot_str[128];
	strftime(boot_str, 128, "Booted on %A, %B %d %Y, at %r", boot_tm);

	/* Print boot time & time since boot */
	char *time = humanTime(info.uptime);
	printf("%s\n%s\n", boot_str, time);

	free(time);
	return 0;
}
