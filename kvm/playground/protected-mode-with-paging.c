#include <assert.h>
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
#include <unistd.h>

#include "kvm_helpers.h"

#define PM 0  // Protected mode
#define PG 31 // Paging enabled

#define EXTRACT_STATUS_FROM_REGISTER(reg, feature) (uint8_t) (reg >> feature) & 0x1
#define SET_FLAG(reg, flag) ((uint8_t)0x1 << flag) | reg

static_assert(sizeof(unsigned) == 4,
	"This program requires that size of unsigned int type is 4.\n");

extern uint8_t start_of_code;
extern uint8_t end_of_code;

void* createPageTable(void *mem)
{
	uint32_t pde = 0x2000 | 0x3;
	memcpy(mem, &pde, 4);

	uint32_t pte_1 = 0x0000 | 0x3;
	memcpy(mem + 0x1000, &pte_1, 4);

	uint32_t pte_2 = 0x1000 | 0x3;
	memcpy(mem + 0x1004, &pte_2, 4);

	uint32_t pte_3 = 0x2000 | 0x3;
	memcpy(mem + 0x1008, &pte_3, 4);

	uint32_t pte_4 = 0x3000 | 0x3;
	memcpy(mem + 0x100c, &pte_4, 4);

	uint32_t pte_5 = 0x4000 | 0x3;
	memcpy(mem + 0x1010, &pte_5, 4);

	uint32_t pte_6 = 0x5000 | 0x3;
	memcpy(mem + 0x1014, &pte_6, 4);

	uint32_t pte_7 = 0x6000 | 0x3;
	memcpy(mem + 0x1030, &pte_7, 4);

	uint32_t pte_8 = 0x7000 | 0x3;
	memcpy(mem + 0x1034, &pte_8, 4);

	uint32_t pte_9 = 0x8000 | 0x3;
	memcpy(mem + 0x1038, &pte_9, 4);

	uint32_t pte_10 = 0x9000 | 0x3;
	memcpy(mem + 0x103c, &pte_10, 4);

	return 0;
}

off_t get_file_size(int fd)
{
	struct stat s;
	if (fstat(fd, &s) < 0) {
		return -1;
	}
	return s.st_size;
}

int read_into_buffer(int fd, uint8_t *buf)
{
	uint8_t temp[32];
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
	int i;
	int a_fd = open("protected-mode-with-paging-a.bin", O_RDONLY);
	if (a_fd == -1) {
		printf("Could not open a.bin.\n");
		return -1;
	}

	int b_fd = open("protected-mode-with-paging-b.bin", O_RDONLY);
	if (b_fd == -1) {
		printf("Could not open b.bin.\n");
		return -1;
	}

	off_t a_fs = get_file_size(a_fd);
	off_t b_fs = get_file_size(b_fd);

	int ret;
	int kvm = open_dev_kvm();

	check_cap_user_memory(kvm);

	int vmfd = create_vm(kvm);

	check_cap_ext_cpuid(kvm);

	struct kvm_cpuid2 *cpuid;
	int nent = 256;

	unsigned long size = sizeof(*cpuid) + nent * sizeof(*cpuid->entries);
	cpuid = (struct kvm_cpuid2*)malloc(size);
	bzero(cpuid, size);
	cpuid->nent = nent;

	ret = ioctl(kvm, KVM_GET_SUPPORTED_CPUID, cpuid);
	printf("CPUID ret no: %d\n", ret);
	if (ret == -1) {
		printf("KVM_GET_SUPPORTED_CPUID could not read CPUID info. Error code: %d\n", ret);
		return -1;
	}

	for (i = 0; i < cpuid->nent; i++) {
		printf("F: 0x%08x, idx: 0x%08x, flags: 0x%08x, eax: 0x%08x, ebx: 0x%08x, ecx: 0x%08x, edx: 0x%08x\n",
		cpuid->entries[i].function, cpuid->entries[i].index, cpuid->entries[i].flags, cpuid->entries[i].eax, cpuid->entries[i].ebx, cpuid->entries[i].ecx, cpuid->entries[i].edx);
	}

	void *mem = mmap_user_memory_region(vmfd, 0x8000, 0x1000, NULL, 0);

	createPageTable(mem);

	int bytes_copied = read_into_buffer(a_fd, mem + 0x3000);
	if (bytes_copied != a_fs) {
		printf("Expected to copy as many bytes as there are in a.bin.\n");
		return -1;
	}

	bytes_copied = read_into_buffer(b_fd, mem + 0x5000);
	if (bytes_copied != b_fs) {
		printf("Expected to copy as many bytes as there are in b.bin.\n");
		return -1;
	}

	int vcpufd = create_vcpu(vmfd);

	ret = ioctl(vcpufd, KVM_SET_CPUID2, cpuid);
	if (ret == -1) {
		printf("KVM_SET_CPUID2 could not set CPUID info. Error code: %d\n", ret);
		return -1;
	}

	struct kvm_run *run = mmap_kvm_run(kvm, vcpufd);

	struct kvm_sregs sregs;

	get_sregs(vcpufd, &sregs);

	sregs.cs.base = 0;
	sregs.cs.selector = 0;

	sregs.cr3 = 0x1000;
	sregs.cr0 = sregs.cr0 | 0x80000001;

	set_sregs(vcpufd, &sregs);

	struct kvm_regs regs = {
		.rip = 0x4000,
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
			printf("KVM_EXIT_FAIL_ENTRY: hardware_entry_failure_reason = 0x%llx\n", (unsigned long long)run->fail_entry.hardware_entry_failure_reason);
			return -1;
		case KVM_EXIT_INTERNAL_ERROR:
			printf("KVM_EXIT_INTERNAL_ERROR: suberror = 0x%x\n", run->internal.suberror);
			printf("KVM_EXIT_INTERNAL_ERROR: size = %d\n", run->internal.ndata);
			return -1;
		}
	}

	return ret;
}
