#pragma once
#include <stdint.h>

void cpu_detect(int cpuid_level);

void family_model(void);
void model_name(void);

/* see kernel kvm_check_cpuid() */
void cpu_address_sizes(void);

int have_avx(void);
int have_sse3(void);
int have_sse4_1(void);
int have_sse4_2(void);
int have_ssse3(void);
int have_fma(void);
int have_xsave(void);
int have_mmx(void);
int have_sse(void);
int have_sse2(void);
int have_rdrand(void);

#define VIRTUALIZATION_NONE 0
#define VIRTUALIZATION_XEN 1
#define VIRTUALIZATION_KVM 2
#define VIRTUALIZATION_QEMU 3
#define VIRTUALIZATION_VMWARE 4
#define VIRTUALIZATION_MICROSOFT 5
#define VIRTUALIZATION_BHYVE 6
#define VIRTUALIZATION_QNX 7
#define VIRTUALIZATION_VM_OTHER 8
int detect_vm_cpuid(void);
