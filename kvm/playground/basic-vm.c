#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/kvm.h>
#include <stdio.h>

#include "kvm_helpers.h"

int main(int argc, char **argv)
{
	const uint8_t code[] = {
		0xba, 0xf8, 0x03,	/* mov $0x3f8, %dx */
		0xb0, 'R',		/* mov $'T', %al */
		0xee,			/* out %al, (%dx) */
		0xb0, 'T',		/* mov $'T', %al */
		0xee,			/* out %al, (%dx) */
		0xb0, ' ',		/* mov $' ', %al */
		0xee,			/* out %al, (%dx) */
		0xb0, 'H',		/* mov $'H', %al */
		0xee,			/* out %al, (%dx) */
		0xb0, 'e',		/* mov $'e', %al */
		0xee,			/* out %al, (%dx) */
		0xb0, 'l',		/* mov $'l', %al */
		0xee,			/* out %al, (%dx) */
		0xb0, 'l',		/* mov $'l', %al */
		0xee,			/* out %al, (%dx) */
		0xb0, 'o',		/* mov $'o', %al */
		0xee,			/* out %al, (%dx) */
		0xb0, '\n',		/* mov $'\n', %al */
		0xee,			/* out %al, (%dx) */
		0xf4,			/* hlt */
	};

	int ret;
	int kvm = open_dev_kvm();

	check_cap_user_memory(kvm);

	int vmfd = create_vm(kvm);

#define MEM_SIZE	0x1000
#define ENTRY_ADDR	0x4000

	void *mem = mmap_user_memory_region(vmfd, MEM_SIZE, ENTRY_ADDR, code,
					    sizeof(code));

	int vcpufd = create_vcpu(vmfd);
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
		.rip = ENTRY_ADDR,
		.rflags = X86_EFLAGS_FIXED,
	};
	set_regs(vcpufd, &regs);

	printf("-------------------\n");
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
			} else
				printf("unhandled KVM_EXIT_IO\n");
			break;
		case KVM_EXIT_FAIL_ENTRY:
			printf("KVM_EXIT_FAIL_ENTRY: hardware_entry_failure_reason = 0x%llx\n",
				(unsigned long long)run->fail_entry.hardware_entry_failure_reason);
			break;
		case KVM_EXIT_INTERNAL_ERROR:
			printf("KVM_EXIT_INTERNAL_ERROR: suberror = 0x%x\n", run->internal.suberror);
			printf("KVM_EXIT_INTERNAL_ERROR: size = %d\n", run->internal.ndata);
			break;
		}
	}

	munmap(mem, MEM_SIZE);

	return ret;
}
