#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cpuid-generic.h"


int main(int argc, char *argv[])
{
	vendor_id();
#if defined(__x86_64__)
	family_model();
	model_name();
	cpu_address_sizes();
	detect_vm_cpuid();

#elif defined(__aarch64__)

#endif
	cpu_flags();

	return 0;
}
