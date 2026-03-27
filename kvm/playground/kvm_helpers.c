#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/kvm.h>
#include <stdio.h>

#include "kvm_helpers.h"

int open_dev_kvm(void)
{
	int kvm = open("/dev/kvm", O_RDWR | O_CLOEXEC);
	if (kvm <= 0) {
		fprintf(stderr, "open /dev/kvm %d\n", kvm);
		exit(1);
	}
	int ret = ioctl(kvm, KVM_GET_API_VERSION, NULL);
	if (ret != KVM_API_VERSION) {
		fprintf(stderr, "KVM_GET_API_VERSION expoected 12 but got %d.",
			ret);
		exit(1);
	}

	return kvm;
}

int run_vcpu(int vcpufd)
{
	int ret;
	if ((ret = ioctl(vcpufd, KVM_RUN, NULL)) == -1) {
		printf("KVM_RUN was unable to start the VM. Error code: %d\n",
		       ret);
		exit(1);
	}
	return ret;
}

void check_cap_user_memory(int kvmfd)
{
	int ret = ioctl(kvmfd, KVM_CHECK_EXTENSION, KVM_CAP_USER_MEMORY);
	if (ret == -1) {
		fprintf(stderr,
			"KVM_CAP_USER_MEM not available. Error code: %d\n",
			ret);
		exit(1);
	}
}

/**
 * Check KVM_GET_SUPPORTED_CPUID is support or not.
 * https://www.kernel.org/doc/html/latest/virt/kvm/api.html
 */
void check_cap_ext_cpuid(int kvmfd)
{
	int ret = ioctl(kvmfd, KVM_CHECK_EXTENSION, KVM_CAP_EXT_CPUID);
	if (ret == -1) {
		fprintf(stderr,
			"KVM_CAP_EXT_CPUID not available. Error code: %d\n",
			ret);
		exit(1);
	}
}

/**
 * Check KVM_GET_EMULATED_CPUID is support or not.
 * https://www.kernel.org/doc/html/latest/virt/kvm/api.html
 */
void check_cap_ext_emul_cpuid(int kvmfd)
{
	int ret = ioctl(kvmfd, KVM_CHECK_EXTENSION, KVM_CAP_EXT_EMUL_CPUID);
	if (ret == -1) {
		fprintf(stderr,
			"KVM_CAP_EXT_EMUL_CPUID not available. Error code: %d\n",
			ret);
		exit(1);
	}
}

void check_cap_get_msr_features(int kvm)
{
	int ret = ioctl(kvm, KVM_CHECK_EXTENSION, KVM_CAP_GET_MSR_FEATURES);
	if (ret == -1) {
		fprintf(stderr,
			"KVM_CAP_GET_MSR_FEATURES not available. Error code: %d\n",
			ret);
		exit(1);
	}
}

int create_vm(int kvmfd)
{
	int vmfd = ioctl(kvmfd, KVM_CREATE_VM, (unsigned long)0);
	if (vmfd == -1) {
		printf("ERROR: KVM_CREATE_VM %d\n", vmfd);
		exit(1);
	}
	return vmfd;
}

int create_vcpu(int vmfd)
{
	int vcpufd = ioctl(vmfd, KVM_CREATE_VCPU, (unsigned long)0);
	if (vcpufd == -1) {
		fprintf(stderr,
			"Could not create VCPU for VM %d. Error code: %d", vmfd,
			vcpufd);
		exit(1);
	}
	return vcpufd;
}

void *mmap_user_memory_region(int vmfd, size_t size, unsigned long gpa,
			      const void *code, size_t code_len)
{
	int ret;
	void *mem = mmap(NULL, size, PROT_READ | PROT_WRITE,
			 MAP_SHARED | MAP_ANONYMOUS, -1, 0);

	if (code) {
		if (code_len > size) {
			fprintf(stderr, "ERROR: code length too large.\n");
			exit(1);
		}
		memcpy(mem, code, code_len);
	}

	struct kvm_userspace_memory_region region = {
		.slot = 0,
		.guest_phys_addr = gpa,
		.memory_size = size,
		.userspace_addr = (uint64_t)mem,
	};

	ret = ioctl(vmfd, KVM_SET_USER_MEMORY_REGION, &region);
	if (ret == -1) {
		fprintf(stderr, "Could not set guest memory. Error code: %d\n",
			ret);
		exit(1);
	}

	return mem;
}

struct kvm_run *mmap_kvm_run(int kvmfd, int vcpufd)
{
	size_t mmap_size;
	struct kvm_run *run;

	mmap_size = ioctl(kvmfd, KVM_GET_VCPU_MMAP_SIZE, NULL);
	run = (struct kvm_run *)mmap(NULL, mmap_size, PROT_READ | PROT_WRITE,
				     MAP_SHARED, vcpufd, 0);

	return run;
}

void get_sregs(int vcpufd, struct kvm_sregs *sregs)
{
	int ret = ioctl(vcpufd, KVM_GET_SREGS, sregs);
	if (ret == -1) {
		printf("KVM_GET_SREGS failed to read special registers. Exit code: %d\n",
		       ret);
		exit(1);
	}
}

void set_sregs(int vcpufd, struct kvm_sregs *sregs)
{
	int ret = ioctl(vcpufd, KVM_SET_SREGS, sregs);
	if (ret == -1) {
		printf("KVM_SET_SREGS failed to update special registers. Exit code: %d\n",
		       ret);
		exit(1);
	}
}

void dump_kvm_sregs(struct kvm_sregs *sregs)
{
#if defined(__x86_64__)
#define segment(name)                                                       \
	printf("%-5s %#016llx %#08x %#08x %-4d\n", #name, sregs->name.base, \
	       sregs->name.limit, sregs->name.selector, sregs->name.type);
#define dtable(name)                                             \
	printf("%-5s %#016llx %#08x\n", #name, sregs->name.base, \
	       sregs->name.limit);
#define pu64(name) printf("%-5s %#016llx\n", #name, sregs->name);

	printf("Dump kvm_sregs\n");
	printf("%-5s %-16s %-8s %-8s %-4s\n", "NAME", "Base", "Limit",
	       "Selector", "Type");
	segment(cs);
	segment(ds);
	segment(es);
	segment(fs);
	segment(gs);
	segment(ss);
	segment(tr);
	segment(ldt);
	dtable(gdt);
	dtable(idt);

	printf("\n");
	pu64(cr0);
	pu64(cr2);
	pu64(cr3);
	pu64(cr4);
	pu64(cr8);
	pu64(efer);
	pu64(apic_base);
#undef segment
#undef dtable
#undef pu64
#else
#error "Unsupport arch"
#endif
}

void get_regs(int vcpufd, struct kvm_regs *regs)
{
	int ret = ioctl(vcpufd, KVM_GET_REGS, regs);
	if (ret == -1) {
		printf("KVM_GET_REGS failed to read special registers. Exit code: %d\n",
		       ret);
		exit(1);
	}
}

void set_regs(int vcpufd, struct kvm_regs *regs)
{
	int ret = ioctl(vcpufd, KVM_SET_REGS, regs);
	if (ret == -1) {
		printf("KVM_SET_REGS failed to update special registers. Exit code: %d\n",
		       ret);
		exit(1);
	}
}

void dump_kvm_regs(struct kvm_regs *regs)
{
#if defined(__x86_64__)
#define pu64(name) printf("%-5s %#016llx ", #name, regs->name);

	printf("Dump kvm_regs\n");
	pu64(rax);
	pu64(rbx);
	pu64(rcx);
	pu64(rdx);
	printf("\n");
	pu64(rsi);
	pu64(rdi);
	pu64(rsp);
	pu64(rbp);
	printf("\n");
	pu64(r8);
	pu64(r9);
	pu64(r10);
	pu64(r11);
	printf("\n");
	pu64(r12);
	pu64(r13);
	pu64(r14);
	pu64(r15);
	printf("\n");
	pu64(rip);
	pu64(rflags);
	printf("\n");
#undef pu64
#else
#error "Unsupport arch"
#endif
}
