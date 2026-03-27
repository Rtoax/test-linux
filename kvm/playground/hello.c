/**
 * File: qemu.c
 * Author: Qiang Li
 * Recode: Rong Tao <rtoax@foxmail.com>
 * Date: 2022.06.03
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/kvm.h>

#include "kvm_helpers.h"

#define MEM_SIZE 0x1000

#if !defined(__x86_64__)
# warning "Not support arch, just x86_64 now."
#endif

int main(void)
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

#define ENTRY_ADDR	0x0
	ram = mmap_user_memory_region(vmfd, MEM_SIZE, ENTRY_ADDR,
					code, sizeof(code));

	vcpufd = create_vcpu(vmfd);

	run = mmap_kvm_run(kvmfd, vcpufd);

	get_sregs(vcpufd, &sregs);

	sregs.cs.base = 0;
	sregs.cs.selector = 0;

	dump_kvm_sregs(&sregs);

	set_sregs(vcpufd, &sregs);

	struct kvm_regs regs = {
		.rax = 5,
		.rbx = 2,
		.rip = ENTRY_ADDR,
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
			putchar(*(((char *)run) + run->io.data_offset));
			break;
		case KVM_EXIT_FAIL_ENTRY:
			puts("entry error.");
			return -1;
		case KVM_EXIT_INTERNAL_ERROR:
		case KVM_EXIT_MMIO:
		default:
			printf("KVM_EXIT_INTERNAL_ERROR: suberror = 0x%x\n", run->internal.suberror);
			printf("KVM_EXIT_INTERNAL_ERROR: size = %d\n", run->internal.ndata);
			puts("other error.");
			printf("exit_reason: %d\n", run->exit_reason);
			return -1;
		}
	}
}
