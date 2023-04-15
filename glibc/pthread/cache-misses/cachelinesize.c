/**
 * This tool use to get level3 cacheline size
 *
 * Copyright (C) CESTC, Co.
 *
 * 2023-03-24	Rong Tao	Create this.
 */
#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
	printf("%ld\n", sysconf(_SC_LEVEL3_CACHE_LINESIZE));
	return 0;
}
