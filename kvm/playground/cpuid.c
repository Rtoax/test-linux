/**
 * Get kvm CPUID
 *
 * refs:
 * [0] https://www.kernel.org/doc/html/latest/virt/kvm/api.html
 * [1] https://lwn.net/Articles/813719/
 */
#include <cpuid.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/kvm.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>

#include "kvm_helpers.h"

extern uint8_t start_of_code;
extern uint8_t end_of_code;

int main(int argc, char **argv)
{
	int i;
	int ret;
	int kvm = open_dev_kvm();

	check_cap_user_memory(kvm);

	int vmfd = create_vm(kvm);

	check_cap_ext_cpuid(kvm);
	check_cap_ext_emul_cpuid(kvm);

	struct kvm_cpuid2 *cpuid;
	/**
	 * See kernel commit("KVM: x86: Return -E2BIG when KVM_GET_SUPPORTED_CPUID
	 * hits max entries")
	 */
#ifndef KVM_MAX_CPUID_ENTRIES
#define KVM_MAX_CPUID_ENTRIES 256
#endif
	int nent = KVM_MAX_CPUID_ENTRIES;
	unsigned long size = sizeof(*cpuid) + nent * sizeof(*cpuid->entries);

	cpuid = (struct kvm_cpuid2*)malloc(size);
	bzero(cpuid, size);

	cpuid->nent = nent;

	/**
	 * KVM_GET_SUPPORTED_CPUID
	 * - This ioctl returns x86 cpuid features which are supported by both
	 *   the hardware and kvm in its default configuration.
	 *
	 * KVM_GET_EMULATED_CPUID
	 * - This ioctl returns x86 cpuid features which are emulated by kvm.
	 *   Userspace can use the information returned by this ioctl to query
	 *   which features are emulated by kvm instead of being present natively.
	 */
	ret = ioctl(kvm, KVM_GET_SUPPORTED_CPUID, cpuid);
	printf("CPUID ret no: %d\n", ret);
	if (ret == -1) {
		printf("KVM_GET_SUPPORTED_CPUID could not read CPUID info. Error code: %d, %d\n",
			ret, cpuid->nent);
		return -1;
	}

	for (i = 0; i < cpuid->nent; i++) {
		printf("%-4d F: 0x%08x, idx: 0x%08x, flags: 0x%08x, eax: 0x%08x, ebx: 0x%08x, ecx: 0x%08x, edx: 0x%08x\n",
			i,
			cpuid->entries[i].function,
			cpuid->entries[i].index,
			cpuid->entries[i].flags,
			cpuid->entries[i].eax,
			cpuid->entries[i].ebx,
			cpuid->entries[i].ecx,
			cpuid->entries[i].edx);
	}

	void __unused *mem = mmap_user_memory_region(vmfd, 0x1000, 0x1000,
					&start_of_code, &end_of_code - &start_of_code);

	int vcpufd = create_vcpu(vmfd);

	ret = ioctl(vcpufd, KVM_SET_CPUID2, cpuid);
	if (ret == -1) {
		printf("KVM_SET_CPUID2 could not set CPUID info. Error code: %d\n", ret);
		return -1;
	}

	struct kvm_run *run = mmap_kvm_run(kvm, vcpufd);

	struct kvm_sregs sregs;

	get_sregs(vcpufd, &sregs);

	dump_kvm_sregs(&sregs);

	sregs.cs.base = 0;
	sregs.cs.selector = 0;

	set_sregs(vcpufd, &sregs);

	struct kvm_regs regs = {
		.rax = 5,
		.rbx = 2,
		.rsp = 0x2000,
		.rip = 0x1000,
		.rflags = X86_EFLAGS_FIXED,
	};
	set_regs(vcpufd, &regs);

	while (1) {
		run_vcpu(vcpufd);

		switch (run->exit_reason) {
		case KVM_EXIT_HLT:
			puts("KVM_EXIT_HLT");
			return 0;
		case KVM_EXIT_IO:
			if (run->io.direction == KVM_EXIT_IO_OUT &&
				run->io.size == 1 &&
				run->io.port == 0x3f8 &&
				run->io.count == 1) {
			putchar(*(((char *)run) + run->io.data_offset));
				putchar('\n');
			} else
				printf("unhandled KVM_EXIT_IO\n");
			break;
		case KVM_EXIT_FAIL_ENTRY:
			printf("KVM_EXIT_FAIL_ENTRY: hardware_entry_failure_reason = 0x%llx\n",
				(unsigned long long)run->fail_entry.hardware_entry_failure_reason);
			break;
		case KVM_EXIT_INTERNAL_ERROR:
			printf("KVM_EXIT_INTERNAL_ERROR: suberror = 0x%x\n",
				 run->internal.suberror);
			printf("KVM_EXIT_INTERNAL_ERROR: size = %d\n", run->internal.ndata);
			break;
		}
	}

	return ret;
}
