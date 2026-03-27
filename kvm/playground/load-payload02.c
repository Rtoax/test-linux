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

#include "kvm_helpers.h"

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

	check_cap_user_memory(kvm);

	int vmfd = create_vm(kvm);

	void __unused *mem = mmap_user_memory_region(vmfd, 0x1000, 0x1000,
					buf, fsize);

	int vcpufd = create_vcpu(vmfd);

	struct kvm_run *run = mmap_kvm_run(kvm, vcpufd);

	struct kvm_sregs sregs;

	get_sregs(vcpufd, &sregs);

	sregs.cs.base = 0;
	sregs.cs.selector = 0;

	dump_kvm_sregs(&sregs);

	set_sregs(vcpufd, &sregs);

	struct kvm_regs regs = {
		.rax = 5,
		.rbx = 2,
		.rdx = 0x3f8,
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
