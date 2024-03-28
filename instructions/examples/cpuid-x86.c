#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <cpuid.h>
#include "cpuid-generic.h"
#include "cpuid-x86.h"

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))


static inline void cpuid(unsigned int op, unsigned int *eax, unsigned int *ebx,
			 unsigned int *ecx, unsigned int *edx)
{
	*eax = op;
	*ecx = 0;

	asm volatile("cpuid"
		: "=a" (*eax),
		  "=b" (*ebx),
		  "=c" (*ecx),
		  "=d" (*edx)
		: "0" (*eax), "2" (*ecx)
		: "memory");
}

unsigned int x86_family(unsigned int sig)
{
	unsigned int x86;

	x86 = (sig >> 8) & 0xf;

	if (x86 == 0xf)
		x86 += (sig >> 20) & 0xff;

	return x86;
}

unsigned int x86_model(unsigned int sig)
{
	unsigned int fam, model;

	fam = x86_family(sig);

	model = (sig >> 4) & 0xf;

	if (fam >= 0x6)
		model += ((sig >> 16) & 0xf) << 4;

	return model;
}

unsigned int x86_stepping(unsigned int sig)
{
	return sig & 0xf;
}

void cpu_detect(int cpuid_level)
{
	unsigned char family, model, stepping;
	int cache_alignment;
	unsigned short clflush_size;

	/* Intel-defined flags: level 0x00000001 */
	if (cpuid_level >= 0x00000001) {
		unsigned int junk, tfms, cap0, misc;

		cpuid(0x00000001, &tfms, &misc, &junk, &cap0);
		family = x86_family(tfms);
		model = x86_model(tfms);
		stepping = x86_stepping(tfms);

		if (cap0 & (1<<19)) {
			clflush_size = ((misc >> 8) & 0xff) * 8;
			cache_alignment = clflush_size;
		}
		printf("CPU family = %d\n", family);
		printf("Model = %d\n", model);
		printf("Stepping = %d\n", stepping);
		printf("clflush_size = %d\n", clflush_size);
		printf("cache_alignment = %d\n", cache_alignment);
	}
}

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

/* see kernel: arch/x86/kvm/kvm_emulate.h */
static inline bool
is_guest_vendor_intel(uint32_t ebx, uint32_t ecx, uint32_t edx)
{
	return ebx == X86EMUL_CPUID_VENDOR_GenuineIntel_ebx &&
	       ecx == X86EMUL_CPUID_VENDOR_GenuineIntel_ecx &&
	       edx == X86EMUL_CPUID_VENDOR_GenuineIntel_edx;
}

static inline bool
is_guest_vendor_amd(uint32_t ebx, uint32_t ecx, uint32_t edx)
{
	return (ebx == X86EMUL_CPUID_VENDOR_AuthenticAMD_ebx &&
		ecx == X86EMUL_CPUID_VENDOR_AuthenticAMD_ecx &&
		edx == X86EMUL_CPUID_VENDOR_AuthenticAMD_edx) ||
	       (ebx == X86EMUL_CPUID_VENDOR_AMDisbetterI_ebx &&
		ecx == X86EMUL_CPUID_VENDOR_AMDisbetterI_ecx &&
		edx == X86EMUL_CPUID_VENDOR_AMDisbetterI_edx);
}

static inline bool
is_guest_vendor_hygon(uint32_t ebx, uint32_t ecx, uint32_t edx)
{
	return ebx == X86EMUL_CPUID_VENDOR_HygonGenuine_ebx &&
	       ecx == X86EMUL_CPUID_VENDOR_HygonGenuine_ecx &&
	       edx == X86EMUL_CPUID_VENDOR_HygonGenuine_edx;
}

void vendor_id(void)
{
	int	cpuid_level = 0;
	char x86_vendor_id[16] = {0};

	cpuid(0x00000000,
		(unsigned int *)&cpuid_level,
		(unsigned int *)&x86_vendor_id[0],
		(unsigned int *)&x86_vendor_id[8],
		(unsigned int *)&x86_vendor_id[4]);

	uint32_t ebx = *(uint32_t *)&x86_vendor_id[0];
	uint32_t ecx = *(uint32_t *)&x86_vendor_id[8];
	uint32_t edx = *(uint32_t *)&x86_vendor_id[4];

	if (is_guest_vendor_intel(ebx, ecx, edx))
		printf("Vendor: Intel\n");
	else if (is_guest_vendor_amd(ebx, ecx, edx))
		printf("Vendor: AMD\n");
	else if (is_guest_vendor_hygon(ebx, ecx, edx))
		printf("Vendor: Hygon\n");
	else
		printf("Vendor: Unknown\n");

	/* cpuid_level: 22, vendor_id: GenuineIntel */
	printf("cpuid_level: %d, vendor_id: %s\n", cpuid_level, x86_vendor_id);

	cpu_detect(cpuid_level);
}

void family_model(void)
{
	uint32_t eax, ebx, ecx, edx;
	int ret = 0;

	eax = ebx = ecx = edx = 0;

	cpuid(1, &eax, &ebx, &ecx, &edx);

	printf("%#08x %#08x %#08x %#08x \n", eax, ebx, ecx, edx);
}

void model_name(void)
{
	char x86_model_id[64] = {0};
	unsigned int *v = (unsigned int *)x86_model_id;

	cpuid(0x80000002, &v[0], &v[1], &v[2], &v[3]);
	cpuid(0x80000003, &v[4], &v[5], &v[6], &v[7]);
	cpuid(0x80000004, &v[8], &v[9], &v[10], &v[11]);

	x86_model_id[48] = 0;

	/* module_id: Intel(R) Core(TM) i7-10710U CPU @ 1.10GHz */
	printf("module_id: %s\n", x86_model_id);
}

/* see kernel kvm_check_cpuid() */
void cpu_address_sizes(void)
{
	unsigned int x86_virt_bits, x86_phys_bits;
	unsigned int eax, ebx, ecx, edx;

	cpuid(0x80000008, &eax, &ebx, &ecx, &edx);

	x86_virt_bits = (eax >> 8) & 0xff;
	x86_phys_bits = eax & 0xff;

	/* see kernel kvm_check_cpuid() */
	if (x86_virt_bits != 48 && x86_virt_bits != 57 && x86_virt_bits != 0) {
		fprintf(stderr, "ERROR: Invalid vaddr bits %d\n", x86_virt_bits);
		exit(1);
	} else
		printf("Address size: %d bits physical, %d bits virtual.\n",
			x86_phys_bits, x86_virt_bits);
}

int have_avx(void)
{
	unsigned int eax = 0, ebx = 0, ecx = 0, edx = 0;
	cpuid(1, &eax, &ebx, &ecx, &edx);
	return ecx & bit_AVX ? 1 : 0;
}

#define kCPUFeature_SSE		0x01
#define kCPUFeature_SSE2	0x02
#define kCPUFeature_SSE3	0x04
#define kCPUFeature_SSE3_S	0x08
#define kCPUFeature_SSE4_1	0x10
#define kCPUFeature_SSE4_2	0x20
#define kCPUFeature_AVX		0x40

unsigned int checkCPUFeatures(void)
{
	uint32_t xcr0;
	unsigned int eax = 0, ebx = 0, ecx = 0, edx = 0;
	unsigned int features = 0;

	cpuid(1, &eax, &ebx, &ecx, &edx);

	if( (edx & (1 << 25)) != 0 ) {
		features |= kCPUFeature_SSE;
	}
	if( (edx & (1 << 26)) != 0 ) {
		features |= kCPUFeature_SSE2;
	}
	if( (ecx & (1 << 0)) != 0 ) {
		features |= kCPUFeature_SSE3;
	}
	if( (ecx & (1 << 9)) != 0 ) {
		features |= kCPUFeature_SSE3_S;
	}
	if( (ecx & (1 << 19)) != 0 ) {
		features |= kCPUFeature_SSE4_1;
	}
	if( (ecx & (1 << 20)) != 0 ) {
		features |= kCPUFeature_SSE4_2;
	}
	if( (ecx & (1 << 28)) != 0 && (ecx & (1 << 27)) != 0 && (ecx & (1 << 26)) != 0 ) {
#if defined(_MSC_VER)
		xcr0 = _xgetbv();
#else
		__asm__("xgetbv" : "=a" (xcr0) : "c" (0) : "%edx");
#endif
		if((xcr0 & 6) == 6) {
			features |= kCPUFeature_AVX;
		}
	}
	return features;
}

int detect_vm_cpuid(void)
{
	static const struct {
		const char *cpuid;
		int id;
	} cpuid_vendor_table[] = {
		{ "XenVMMXenVMM", VIRTUALIZATION_XEN	},
		{ "KVMKVMKVM",	VIRTUALIZATION_KVM	},
		{ "TCGTCGTCGTCG", VIRTUALIZATION_QEMU	},
		/* http://kb.vmware.com/selfservice/microsites/search.do?language=en_US&cmd=displayKC&externalId=1009458 */
		{ "VMwareVMware", VIRTUALIZATION_VMWARE	},
		/* https://docs.microsoft.com/en-us/virtualization/hyper-v-on-windows/reference/tlfs */
		{ "Microsoft Hv", VIRTUALIZATION_MICROSOFT	},
		/* https://wiki.freebsd.org/bhyve */
		{ "bhyve bhyve ", VIRTUALIZATION_BHYVE	},
		{ "QNXQVMBSQG",   VIRTUALIZATION_QNX	},
	};

	uint32_t eax, ebx, ecx, edx;
	bool hypervisor;

	/* http://lwn.net/Articles/301888/ */

	/* First detect whether there is a hypervisor */
	if (__get_cpuid(1, &eax, &ebx, &ecx, &edx) == 0)
		return VIRTUALIZATION_NONE;

	hypervisor = !!(ecx & 0x80000000U);

	if (hypervisor) {
		union {
			uint32_t sig32[3];
			char text[13];
		} sig = {};
		unsigned j;

		/* There is a hypervisor, see what it is */
		__cpuid(0x40000000U, eax, ebx, ecx, edx);

		sig.sig32[0] = ebx;
		sig.sig32[1] = ecx;
		sig.sig32[2] = edx;

		printf("Virtualization found, CPUID=%s\n", sig.text);

		for (j = 0; j < ARRAY_SIZE(cpuid_vendor_table); j ++)
			if (!strcmp(sig.text, cpuid_vendor_table[j].cpuid))
				return cpuid_vendor_table[j].id;

		return VIRTUALIZATION_VM_OTHER;
	}

	printf("No virtualization found in CPUID\n");
	return VIRTUALIZATION_NONE;
}

