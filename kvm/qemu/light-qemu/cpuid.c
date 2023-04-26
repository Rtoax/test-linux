#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <strings.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/kvm.h>

/**
 * ref: https://hackernoon.com/how-to-emulate-cpuid-in-a-kvm-vm-ihy3yuy
 */
#if defined(__x86_64__)
void print_cpuid(int kvmfd)
{
	int i, ret;
	struct kvm_cpuid2 *cpuid;
	unsigned int size;
	int nent = 4;

	size = sizeof(*cpuid) + nent * sizeof(*cpuid->entries);
	cpuid = (struct kvm_cpuid2 *)malloc(size);
	bzero(cpuid, size);

	cpuid->nent = nent;

	/**
	 * $ sudo bpftrace -e 'kprobe:kvm_dev_ioctl_get_cpuid {printf("%s\n", comm);}'
	 */
	ret = ioctl(kvmfd, KVM_GET_SUPPORTED_CPUID, cpuid);
	if (ret != 0) {
		printf("KVM_GET_SUPPORTED_CPUID could not read CPUID info." \
				" Error code: %d\n", ret);
		return;
	}

	for (i = 0; i < cpuid->nent; i++) {
		printf("F: 0x%08x, idx: 0x%08x, flags: 0x%08x, eax: 0x%08x, ebx: 0x%08x, ecx: 0x%08x, edx: 0x%08x\n",
			cpuid->entries[i].function,
			cpuid->entries[i].index,
			cpuid->entries[i].flags,
			cpuid->entries[i].eax,
			cpuid->entries[i].ebx,
			cpuid->entries[i].ecx,
			cpuid->entries[i].edx);
	}

	free(cpuid);
}
#else
void print_cpuid(int kvmfd) {}
#endif
