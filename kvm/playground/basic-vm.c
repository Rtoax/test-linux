#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/kvm.h>
#include <stdio.h>

int main(int argc, char **argv)
{
	const uint8_t code[] = {
		0xba, 0xf8, 0x03,	/* mov $0x3f8, %dx */
		0x00, 0xd8,			/* add %bl, %al */
		0x04, '1',			/* add $'0', %al */
		0xee,				/* out %al, (%dx) */
		0xb0, '\n',			/* mov $'\n', %al */
		0xee,				/* out %al, (%dx) */
		0xf4,				/* hlt */
	};

	int kvm = open("/dev/kvm", O_RDWR | O_CLOEXEC);
	int ret = ioctl(kvm, KVM_GET_API_VERSION, NULL);
	if (ret != 12) {
		printf("KVM_GET_API_VERSION expoected 12 but got %d.", ret);
		return -1;
	}

	ret = ioctl(kvm, KVM_CHECK_EXTENSION, KVM_CAP_USER_MEMORY);
	if(ret == -1) {
		printf("KVM_CAP_USER_MEM not available. Error code: %d\n", ret);
		return -1;
	}

	int vmfd = ioctl(kvm, KVM_CREATE_VM, (unsigned long)0);
	if(vmfd == -1) {
		printf("There was a problem creating VM. KVM_CREATE_VM exit code: %d\n", vmfd);
		return -1;
	}

	void *mem = mmap(NULL, 0x1000, PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	memcpy(mem, code, sizeof(code));
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

	size_t mmap_size = ioctl(kvm, KVM_GET_VCPU_MMAP_SIZE, NULL);
	struct kvm_run *run = (struct kvm_run*)mmap(NULL, mmap_size,
			PROT_READ | PROT_WRITE,
			MAP_SHARED,
			vcpufd,
			0);

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
		.rip = 0x1000,
		.rflags = 0x2,
	};
	ret = ioctl(vcpufd, KVM_SET_REGS, &regs);
	if (ret == -1) {
		printf("KVM_SET_REGS failed to update registers. Exit code: %d\n", ret);
		return -1;
	}

	while (1) {
		if((ret = ioctl(vcpufd, KVM_RUN, NULL)) == -1) {
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
			printf("KVM_EXIT_INTERNAL_ERROR: suberror = 0x%x\n", run->internal.suberror);
			printf("KVM_EXIT_INTERNAL_ERROR: size = %d\n", run->internal.ndata);
			break;
		}
	}

	return ret;
}
