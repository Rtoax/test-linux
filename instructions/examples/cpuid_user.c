#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
//#include <cpuid.h>

#if defined(__x86_64__)
#include "cpuid-x86.h"

int main(int argc, char *argv[])
{
	vendor_id();
	family_model();
	model_name();
	cpu_address_sizes();

	return 0;
}
#endif
