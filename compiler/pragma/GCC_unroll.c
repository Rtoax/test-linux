/**
 * clang lang loop unroll could be 'enable', 'full' or 'disable'
 *
 * Compile option:
 *  -funroll-loops
 *  -funroll-all-loops
 */
#ifndef __IN_BPF__
#include <stdio.h>
#else
#include <linux/types.h>
#include <bpf/bpf_helpers.h>
#define printf bpf_printk
#endif

void origin(void)
{
	int i, n = 10;

	for (i = 0; i < n; i++)
		printf("%d\n", i);
}

void enable(void)
{
	int i, n = 10;

	#if defined(__clang__)
	#pragma clang loop unroll (enable)
	#elif __GNUC__ >= 8
	#pragma GCC unroll 10
	#endif
	for (i = 0; i < n; i++)
		printf("%d\n", i);
}

void disable(void)
{
	int i, n = 10;

	#if defined(__clang__)
	#pragma clang loop unroll (disable)
	#endif
	for (i = 0; i < n; i++)
		printf("%d\n", i);
}

#if __GNUC__ >= 8
__attribute__((optimize("unroll-loops"))) void unroll_loops(void)
{
	int i, n = 10;

	for (i = 0; i < n; i++)
		printf("%d\n", i);
}
#else
#define unroll_loops()
#endif

int main(void)
{
	origin();
	enable();
	disable();
	unroll_loops();
	return 0;
}
