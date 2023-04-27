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

#include "common.h"

#define MEM_SIZE 0x1000

#if !defined(__x86_64__)
# warning "Not support arch, just x86_64 now."
#endif

int main()
{
	struct kvm_sregs sregs;
	int ret;
	int kvmfd, vmfd, kfd, vcpufd;
	unsigned char __unused *ram;
	struct kvm_run *run;
	char code[MEM_SIZE];

	kvmfd = open_dev_kvm();

	check_cap_user_memory(kvmfd);

	vmfd = create_vm(kvmfd);

	kfd = open("hello.bin", O_RDONLY);
	if (kfd <= 0) {
		perror("open(hello.bin)");
		return -1;
	}
	ret = read(kfd, code, MEM_SIZE);
	if (ret <= 0) {
		perror("read(hello.bin)");
		return -1;
	}

	ram = mmap_user_memory_region(vmfd, MEM_SIZE, 0,
					code, sizeof(code));

	vcpufd = create_vcpu(vmfd);

	run = mmap_kvm_run(kvmfd, vcpufd);

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
