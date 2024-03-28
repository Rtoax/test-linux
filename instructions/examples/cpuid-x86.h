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

void vendor_id(void);
void family_model(void);
void model_name(void);

/* see kernel kvm_check_cpuid() */
void cpu_address_sizes(void);

int have_avx(void);

#define kCPUFeature_SSE		0x01
#define kCPUFeature_SSE2	0x02
#define kCPUFeature_SSE3	0x04
#define kCPUFeature_SSE3_S	0x08
#define kCPUFeature_SSE4_1	0x10
#define kCPUFeature_SSE4_2	0x20
#define kCPUFeature_AVX		0x40

unsigned int checkCPUFeatures(void);
