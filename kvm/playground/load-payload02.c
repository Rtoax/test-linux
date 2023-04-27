#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/kvm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "common.h"

extern uint8_t start_of_code;
extern uint8_t end_of_code;

off_t get_file_size(int fd)
{
	struct stat buf;
	if (fstat(fd, &buf) < 0) {
		return -1;
	}
	return buf.st_size;
}

int read_into_buffer(int fd, char* buf)
{
	char temp[32];
	int r = read(fd, &temp, 32);
	int total_bytes_copied = 0;

	while (r != 0) {
		memcpy(buf + total_bytes_copied, temp, r);
		total_bytes_copied += r;
		r = read(fd, &temp, 32);
	}
	return total_bytes_copied;
}

int main(int argc, char **argv)
{
	int payload_fd = open("load-payload02-program.bin", O_RDONLY);
	off_t fsize = get_file_size(payload_fd);
	void *buf = malloc(fsize);

	if (read_into_buffer(payload_fd, buf) != fsize)
		return -1;

	int ret;
	int kvm = open_dev_kvm();

	ret = ioctl(kvm, KVM_CHECK_EXTENSION, KVM_CAP_USER_MEMORY);
	if (ret == -1) {
		printf("KVM_CAP_USER_MEM not available. Error code: %d\n", ret);
		return -1;
	}

	int vmfd = ioctl(kvm, KVM_CREATE_VM, (unsigned long)0);
	if (vmfd == -1) {
		printf("There was a problem creating VM. KVM_CREATE_VM exit code: %d\n", vmfd);
		return -1;
	}

	void *mem = mmap(NULL, 0x1000,
		PROT_READ | PROT_WRITE, MAP_SHARED | MAP_ANONYMOUS, -1, 0);
	memcpy(mem, buf, fsize);

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
			PROT_READ | PROT_WRITE, MAP_SHARED, vcpufd, 0);
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
		.rdx = 0x3f8,
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
