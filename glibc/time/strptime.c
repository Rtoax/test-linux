#ifndef _XOPEN_SOURCE
#define _XOPEN_SOURCE
#endif
#include <stdio.h>
#include <time.h>
#include <string.h>
#include "time_helpers.h"

void test(const char *s, const char *fmt)
{
	struct tm t4;
	memset(&t4, 0, sizeof(t4));

	printf("---- strptime(\"%s\", \"%s\")\n", s, fmt);
	if (!strptime(s, fmt, &t4)) {
		fprintf(stderr, "Bad '%s', '%s'\n", s, fmt);
		return;
	}

	print_tm(&t4);
}

int main(void)
{
	test("335-19:01:43", "%j-%H:%M:%S");
	test("2026-07-23 14:30:00", "%Y-%m-%d %H:%M:%S");
	test("09:00:11 AM", "%I:%M:%S %p");
	test("2026-07-23 08:00:11 AM", "%Y-%m-%d %I:%M:%S %p");
	return 0;
}
