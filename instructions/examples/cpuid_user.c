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
	printf("AVX: %s\n", have_avx() ? "support" : "NOTREACHEDt support");
	detect_vm_cpuid();

#elif defined(__aarch64__)

#endif
	return 0;
}
