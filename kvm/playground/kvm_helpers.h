#pragma once

#if defined(__x86_64__)
#include <asm/processor-flags.h> /* X86_EFLAGS_ */
#endif

#define __unused __attribute__((unused))

int open_dev_kvm(void);
int create_vm(int kvmfd);
int create_vcpu(int vmfd);
int run_vcpu(int vcpufd);

void check_cap_user_memory(int kvmfd);
void check_cap_ext_cpuid(int kvmfd);
void check_cap_ext_emul_cpuid(int kvmfd);
void check_cap_get_msr_features(int kvm);

void *mmap_user_memory_region(int vmfd, size_t size, unsigned long gpa,
			      const void *code, size_t code_len);
struct kvm_run *mmap_kvm_run(int kvmfd, int vcpufd);

void get_sregs(int vcpufd, struct kvm_sregs *sregs);
void set_sregs(int vcpufd, struct kvm_sregs *sregs);
void dump_kvm_sregs(struct kvm_sregs *sregs);

void get_regs(int vcpufd, struct kvm_regs *regs);
void set_regs(int vcpufd, struct kvm_regs *regs);
void dump_kvm_regs(struct kvm_regs *regs);
