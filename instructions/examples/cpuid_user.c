/**
 * You can run in guestos
 *
 *     $ while :; do taskset -c 1 ./cpuid_user ; done
 *
 * Then, tracing tracepoint:kvm:kvm_cpuid and count 'comm', like
 * ../../kvm/emulate/cpuid/kvm_cpuid.tp.bt did, you'll get:
 *
 *     @[CPU 0/KVM]: 13469
 *     @[CPU 3/KVM]: 24445
 *     @[CPU 2/KVM]: 57177
 *     @[CPU 1/KVM]: 258910
 */
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
