/**
 * File: qemu.c
 * Author: Qiang Li
 * Recode: Rong Tao <rongtao@cestc.cn>
 * Date: 2022.06.03
 *
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/kvm.h>

#include "qemu.h"

#define MEM_SIZE 0x1000

#if !defined(__x86_64__)
# warning "Not support arch, just x86_64 now."
#endif

int main()
{
	struct kvm_sregs sregs;
	int ret, n;
	int kvmfd, vmfd, kfd, vcpufd;
	unsigned char *ram;
	int mmap_size;
	struct kvm_run *run;

	kvmfd = open("/dev/kvm", O_RDWR);
	if (kvmfd <= 0) {
		fprintf(stderr, "open /dev/kvm %d\n", kvmfd);
		return -1;
	}
	ioctl(kvmfd, KVM_GET_API_VERSION, NULL);
	vmfd = ioctl(kvmfd, KVM_CREATE_VM, 0);
	if (vmfd <= 0) {
		fprintf(stderr, "ioctl KVM_CREATE_VM, %d\n", vmfd);
		return -1;
	}

	ram = mmap(NULL, MEM_SIZE, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	kfd = open("test.bin", O_RDONLY);
	if (kfd <= 0) {
		perror("open(test.bin)");
		return -1;
	}
	ret = read(kfd, ram, MEM_SIZE);
	if (ret <= 0) {
		perror("read(test.bin)");
		return -1;
	}

	struct kvm_userspace_memory_region mem = {
		.slot = 0,
		.guest_phys_addr = 0,
		.memory_size = MEM_SIZE,
		.userspace_addr = (unsigned long)ram,
	};

	ret = ioctl(vmfd, KVM_SET_USER_MEMORY_REGION, &mem);
	if (ret != 0) {
		perror("ioctl");
		return -1;
	}

	vcpufd = ioctl(vmfd, KVM_CREATE_VCPU, 0);
	mmap_size = ioctl(kvmfd, KVM_GET_VCPU_MMAP_SIZE, NULL);

	run = mmap(NULL, mmap_size, PROT_READ | PROT_WRITE, MAP_SHARED, vcpufd, 0);

	ret = ioctl(vcpufd, KVM_GET_SREGS, &sregs);
#if defined(__x86_64__)
	sregs.cs.base = 0;
	sregs.cs.selector = 0;
#endif
	ret = ioctl(vcpufd, KVM_SET_SREGS, &sregs);
	struct kvm_regs regs = {
		/* Running from 'start:' in test.S */
#if defined(__x86_64__)
		.rip = 0,
#endif
	};
	ret = ioctl(vcpufd, KVM_SET_REGS, &regs);

	print_cpuid(kvmfd);

	while (1) {
		ret = ioctl(vcpufd, KVM_RUN, NULL);
		if (ret == -1) {
			printf("exit unknown.\n");
			return -1;
		}
		switch (run->exit_reason) {
			case KVM_EXIT_HLT:
				puts("KVM_EXIT_HLT");
				return 0;
			case KVM_EXIT_IO:
				putchar(*(((char *)run) + run->io.data_offset));
				break;
			case KVM_EXIT_FAIL_ENTRY:
				puts("entry error.");
				return -1;
			case KVM_EXIT_INTERNAL_ERROR:
			case KVM_EXIT_MMIO:
			default:
				puts("other error.");
				printf("exit_reason: %d\n", run->exit_reason);
				return -1;
		}
	}
}
