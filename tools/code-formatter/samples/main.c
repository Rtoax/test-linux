// SPDX-License-Identifier: GPL-2.0
/**
 * Copyright (C) 2024-2026 Rong Tao
 */
#include    <stdio.h>

#define __MACRO( a,         b, c )

static int a = 1;

/* Space indent will be removed */
static int b;

void func(void)
{
	return;
}

// This is main program
int main(void)
{
	printf("Hello.\n");
	/*  */
	func();
	func2();
	func3();
	func4();

	if (a > 1)
		return a;
	if (b < 1) {
		return 1;
	}

	return 0;
}
