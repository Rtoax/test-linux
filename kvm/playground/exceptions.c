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

static_assert(sizeof(unsigned) == 4,
	"This program requires that size of unsigned int type is 4.\n");

struct idt_entry {
	unsigned short base_lo;
	unsigned short sel;
	unsigned char always0;
	unsigned char flags;
	unsigned short base_hi;
	unsigned char padding[8];
} __attribute__((packed));

struct gdtNullEntry {
	unsigned char always0[8];
} __attribute__((packed));

struct gdtEntry {
	unsigned char padding_1[5];
	unsigned char type;
	unsigned char flags; /* lower byte */
	unsigned char padding_2[2];

} __attribute__((packed));


void createGdtTable(void *mem)
{
	struct gdtNullEntry nullEntry = {};
	struct gdtEntry csEntry = {
		.type = 0x9a,
		.flags = 0xa0
	};

	struct gdtEntry __unused dsEntry = {
		.type = 0x92,
		.flags = 0xa0
	};

	memcpy(mem, &nullEntry, 8);
	memcpy(mem + 8, &csEntry, 8);
}

void createIdt(void *mem)
{
	int i;
	struct idt_entry e = {
		.base_lo = 0x9000,
		.sel = 0x8,
		.flags = 0x8e,
	};

	for (i = 0; i < 256; i++)
		memcpy(mem + i * 16, &e, 16);
}

void createPageTable(void *mem)
{
	uint64_t pml4e = 0x2000 | 0x3;
	memcpy(mem, &pml4e, 8);

	uint64_t pdpte = 0x3000 | 0x3;
	memcpy(mem + 0x1000, &pdpte, 8);

	uint64_t pde = 0x4000 | 0x3;
	memcpy(mem + 0x2000, &pde, 8);

	uint64_t pte_1 = 0x0000 | 0x3;
	memcpy(mem + 0x3000, &pte_1, 8);

	uint64_t pte_2 = 0x1000 | 0x3;
	memcpy(mem + 0x3008, &pte_2, 8);

	uint64_t pte_3 = 0x2000 | 0x3;
	memcpy(mem + 0x3010, &pte_3, 8);

	uint64_t pte_4 = 0x3000 | 0x3;
	memcpy(mem + 0x3018, &pte_4, 8);

	uint64_t pte_5 = 0x4000 | 0x3;
	memcpy(mem + 0x3020, &pte_5, 8);

	uint64_t pte_6 = 0x5000 | 0x3;
	memcpy(mem + 0x3028, &pte_6, 8);

	uint64_t pte_7 = 0x6000 | 0x3;
	memcpy(mem + 0x3030, &pte_7, 8);

	uint64_t pte_8 = 0x7000 | 0x3;
	memcpy(mem + 0x3038, &pte_8, 8);

	uint64_t pte_9 = 0x8000 | 0x3;
	memcpy(mem + 0x3040, &pte_9, 8);

	uint64_t pte_10 = 0x9000 | 0x3;
	memcpy(mem + 0x3048, &pte_10, 8);

	uint64_t pte_11 = 0xa000 | 0x3;
	memcpy(mem + 0x3050, &pte_11, 8);

	uint64_t pte_12 = 0xb000 | 0x3;
	memcpy(mem + 0x3058, &pte_12, 8);

	uint64_t pte_13 = 0xc000 | 0x3;
	memcpy(mem + 0x3060, &pte_13, 8);

	uint64_t pte_14 = 0xd000 | 0x3;
	memcpy(mem + 0x3068, &pte_14, 8);

	uint64_t pte_15 = 0xe000 | 0x3;
	memcpy(mem + 0x3070, &pte_15, 8);

	uint64_t pte_16 = 0xf000 | 0x3;
	memcpy(mem + 0x3078, &pte_16, 8);
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
	int a_fd = open(".output/exceptions-a.asm.o", O_RDONLY);
	if (a_fd == -1) {
		printf("Could not open a.asm.o\n");
		return -1;
	}

	int handler_fd = open(".output/exceptions-handler.asm.o", O_RDONLY);
	if (handler_fd == -1) {
		printf("Could not open handler.asm.o\n");
		return -1;
	}

	off_t a_fs = get_file_size(a_fd);
	off_t handler_fs = get_file_size(handler_fd);
	int ret;
	int kvm = open_dev_kvm();

	check_cap_user_memory(kvm);

	int vmfd = create_vm(kvm);

	check_cap_ext_cpuid(kvm);
	check_cap_get_msr_features(kvm);

#define MEM_SIZE	0x10000

	void *mem = mmap_user_memory_region(vmfd, MEM_SIZE, 0x0, NULL, 0);

	createGdtTable(mem);
	createPageTable(mem + 0x1000);
	createIdt(mem + 0xc000);

	int bytes_copied = read_into_buffer(a_fd, mem + 0x6000);
	if (bytes_copied != a_fs) {
		printf("Expected to copy as many bytes as there are in a.bin.\n");
		return -1;
	}

	bytes_copied = read_into_buffer(handler_fd, mem + 0x9000);
	if (bytes_copied != handler_fs) {
		printf("Expected to copy as many bytes as there are in handler.bin.\n");
		return -1;
	}

	int vcpufd = create_vcpu(vmfd);

	struct kvm_run *run = mmap_kvm_run(kvm, vcpufd);

	struct kvm_sregs sregs;
	get_sregs(vcpufd, &sregs);

	sregs.gdt.base = 0x0;
	sregs.gdt.limit = 0x17;

	sregs.idt.base = 0xc000;
	sregs.idt.limit = 0xfff;

	sregs.cs.base = 0;
	sregs.cs.selector = 0x8;
	sregs.cs.l = 0x1;

	sregs.cr3 = 0x1000;
	sregs.cr4 = sregs.cr4 | 0x20;
	sregs.efer = sregs.efer | 0x500;
	sregs.cr0 = sregs.cr0 | 0x80000001;

	dump_kvm_sregs(&sregs);

	printf("IDT base: 0x%llx\n", sregs.idt.base);
	printf("IDT limit: 0x%x\n", sregs.idt.limit);

	set_sregs(vcpufd, &sregs);

	struct kvm_regs regs;
	get_regs(vcpufd, &regs);

	regs.rip = 0x6000;
	regs.rflags = X86_EFLAGS_FIXED;

	dump_kvm_regs(&regs);

	set_regs(vcpufd, &regs);

	while (1) {
		run_vcpu(vcpufd);

		switch (run->exit_reason) {
		case KVM_EXIT_HLT:
			puts("\nKVM_EXIT_HLT");
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
			return -1;
		case KVM_EXIT_INTERNAL_ERROR:
			printf("KVM_EXIT_INTERNAL_ERROR: suberror = 0x%x\n", run->internal.suberror);
			printf("KVM_EXIT_INTERNAL_ERROR: size = %d\n", run->internal.ndata);
			return -1;
		case KVM_EXIT_SHUTDOWN:
			printf("KVM_EXIT_SHUTDOWN\n");
			return -1;
		default:
			printf("Ret code: %i\n", run->exit_reason);
			return -1;
		}
	}

	return ret;
}
