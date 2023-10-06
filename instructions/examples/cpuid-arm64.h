#pragma once

int get_cpuid(unsigned long *flags)
{
	unsigned long cpuid;
	asm("mrs %0, MIDR_EL1" : "=r" (cpuid));
	*flags = cpuid;
	return 0;
}

#include "cpuid-generic.h"
