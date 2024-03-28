#pragma once
#include <stdint.h>

unsigned int x86_family(unsigned int sig);
unsigned int x86_model(unsigned int sig);
unsigned int x86_stepping(unsigned int sig);
void cpu_detect(int cpuid_level);

/* CPUID vendors */
#define X86EMUL_CPUID_VENDOR_AuthenticAMD_ebx 0x68747541
#define X86EMUL_CPUID_VENDOR_AuthenticAMD_ecx 0x444d4163
#define X86EMUL_CPUID_VENDOR_AuthenticAMD_edx 0x69746e65

#define X86EMUL_CPUID_VENDOR_AMDisbetterI_ebx 0x69444d41
#define X86EMUL_CPUID_VENDOR_AMDisbetterI_ecx 0x21726574
#define X86EMUL_CPUID_VENDOR_AMDisbetterI_edx 0x74656273

#define X86EMUL_CPUID_VENDOR_HygonGenuine_ebx 0x6f677948
#define X86EMUL_CPUID_VENDOR_HygonGenuine_ecx 0x656e6975
#define X86EMUL_CPUID_VENDOR_HygonGenuine_edx 0x6e65476e

#define X86EMUL_CPUID_VENDOR_GenuineIntel_ebx 0x756e6547
#define X86EMUL_CPUID_VENDOR_GenuineIntel_ecx 0x6c65746e
#define X86EMUL_CPUID_VENDOR_GenuineIntel_edx 0x49656e69

#define X86EMUL_CPUID_VENDOR_CentaurHauls_ebx 0x746e6543
#define X86EMUL_CPUID_VENDOR_CentaurHauls_ecx 0x736c7561
#define X86EMUL_CPUID_VENDOR_CentaurHauls_edx 0x48727561

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
