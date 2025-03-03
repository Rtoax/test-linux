/* Copyright (C) 2025 CESTC, Co. All rights reserved. */
/* 2025-02-08	Rong Tao	Create this */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "helpers.h"

int main(int argc, char *argv[])
{
	struct timeval tv;

	printf("Hello world.\n");
	proc_display_maps(stderr, "MAIN");

	/* Call vdso function */
	gettimeofday(&tv, NULL);
	printf("tv_sec = %ld\n", tv.tv_sec);

	return 0;
}
