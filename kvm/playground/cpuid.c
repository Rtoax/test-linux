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

extern uint8_t start_of_code;
extern uint8_t end_of_code;

int main(int argc, char **argv)
{
	int i;
	int kvm = open("/dev/kvm", O_RDWR | O_CLOEXEC);
	int ret = ioctl(kvm, KVM_GET_API_VERSION, NULL);
	if (ret != KVM_API_VERSION) {
		printf("KVM_GET_API_VERSION expected 12 but got %d.", ret);
		return -1;
	}

	ret = ioctl(kvm, KVM_CHECK_EXTENSION, KVM_CAP_USER_MEMORY);
	if (ret == -1) {
		printf("KVM_CAP_USER_MEM not available. Error code: %d\n", ret);
		return -1;
	}

	/**
	 * Check KVM_GET_SUPPORTED_CPUID is support or not.
	 * https://www.kernel.org/doc/html/latest/virt/kvm/api.html
	 */
	ret = ioctl(kvm, KVM_CHECK_EXTENSION, KVM_CAP_EXT_CPUID);
	if(ret == -1) {
		printf("KVM_CAP_EXT_CPUID not available. Error code: %d\n", ret);
		return -1;
	}

	/**
	 * Check KVM_GET_EMULATED_CPUID is support or not.
	 * https://www.kernel.org/doc/html/latest/virt/kvm/api.html
	 */
	ret = ioctl(kvm, KVM_CHECK_EXTENSION, KVM_CAP_EXT_EMUL_CPUID);
	if(ret == -1) {
		printf("KVM_CAP_EXT_CPUID not available. Error code: %d\n", ret);
		return -1;
	}

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

	int vmfd = ioctl(kvm, KVM_CREATE_VM, (unsigned long)0);
	if (vmfd == -1) {
		printf("There was a problem creating VM. KVM_CREATE_VM exit code: %d\n", vmfd);
		return -1;
	}

	void *mem = mmap(NULL, 0x1000,
			PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS,
			-1,
			0);

	memcpy(mem, &start_of_code, &end_of_code - &start_of_code);
	struct kvm_userspace_memory_region region = {
		.slot = 0,
		.guest_phys_addr = 0x1000,
		.memory_size = 0x1000,
		.userspace_addr = (uint64_t)mem,
	};

	ret = ioctl(vmfd, KVM_SET_USER_MEMORY_REGION, &region);
	if (ret == -1) {
		printf("Could not set guest memory. Error code: %d\n", ret);
		return -1;
	}

	int vcpufd = ioctl(vmfd, KVM_CREATE_VCPU, (unsigned long)0);
	if (vcpufd == -1) {
		printf("Could not create VCPU for VM %d. Error code: %d", vmfd, vcpufd);
		return -1;
	}

	ret = ioctl(vcpufd, KVM_SET_CPUID2, cpuid);
	if (ret == -1) {
		printf("KVM_SET_CPUID2 could not set CPUID info. Error code: %d\n", ret);
		return -1;
	}

	size_t mmap_size = ioctl(kvm, KVM_GET_VCPU_MMAP_SIZE, NULL);

	struct kvm_run *run = (struct kvm_run*)mmap(NULL, mmap_size, PROT_READ | PROT_WRITE, MAP_SHARED, vcpufd, 0);
	struct kvm_sregs sregs;

	ret = ioctl(vcpufd, KVM_GET_SREGS, &sregs);
	if (ret == -1) {
		printf("KVM_GET_REGS failed to read special registers. Exit code: %d\n", ret);
		return -1;
	}

	sregs.cs.base = 0;
	sregs.cs.selector = 0;

	ret = ioctl(vcpufd, KVM_SET_SREGS, &sregs);
	if (ret == -1) {
		printf("KVM_SET_SREGS failed to update special registers. Exit code: %d\n", ret);
		return -1;
	}

	struct kvm_regs regs = {
		.rax = 5,
		.rbx = 2,
		.rsp = 0x2000,
		.rip = 0x1000,
		.rflags = 0x2,
	};
	ret = ioctl(vcpufd, KVM_SET_REGS, &regs);
	if (ret == -1) {
		printf("KVM_SET_REGS failed to update registers. Exit code: %d\n", ret);
		return -1;
	}

	while (1) {
		if ((ret = ioctl(vcpufd, KVM_RUN, NULL)) == -1) {
			printf("KVM_RUN was unable to start the VM. Error code: %d\n", ret);
			return -1;
		}

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
