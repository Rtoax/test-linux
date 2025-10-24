#include <stdio.h>
#include "cpuid-generic.h"
#include "cpuid-arm64.h"


int get_cpuid(unsigned long *flags)
{
	unsigned long cpuid;
	asm("mrs %0, MIDR_EL1" : "=r" (cpuid));
	*flags = cpuid;
	return 0;
}

int vendor_id(void)
{
	unsigned long cpuid;
	unsigned int vendor_id;

	get_cpuid(&cpuid);
	printf("CPUID from register:  0x%016lx\n",  cpuid);

	vendor_id = cpuid >> 24 & 0xff;
	printf("CPUID vendor ID    :  0x%16x\n",  vendor_id);

	return vendor_id;
}

int cpu_flags(void)
{
	/* TODO */
	return 0;
}
