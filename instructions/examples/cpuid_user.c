#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cpuid-generic.h"


int main(int argc, char *argv[])
{
#if defined(__x86_64__)
	vendor_id();
	family_model();
	model_name();
	cpu_address_sizes();
	detect_vm_cpuid();

	cpu_flags();
#elif defined(__aarch64__)
	vendor_id();
	cpu_flags();
#elif defined(__sw_64__)
# warning "Not support sw_64 yet."
#endif

	return 0;
}
