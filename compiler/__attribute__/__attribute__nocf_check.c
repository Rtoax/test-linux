#include <stdio.h>
#include <stdbool.h>

/**
 * man gcc
 * Enable code instrumentation of control-flow transfers to increase
 * program security by checking that target addresses of control-flow
 * transfer instructions.
 *
 * main:
 * .LFB1:
 * 	.cfi_startproc
 * 	endbr64           << -fcf-protection
 * 	pushq	%rbp
 *
 * endbr64,endbr32 is part of Intel CET. CET is hareware protection of
 * Return-oriented Programming (ROP) and Jump/Call-oriented Programming (JOP/COP)
 */
#define __noendbr       __attribute__((nocf_check))

/* No endbr64 insn in front of func() */
__noendbr int func(bool disable)
{
	return 0;
}

int main(void)
{
	return 0;
}
