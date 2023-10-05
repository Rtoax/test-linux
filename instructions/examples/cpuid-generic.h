#pragma once

#define VIRTUALIZATION_NONE 0
#define VIRTUALIZATION_XEN 1
#define VIRTUALIZATION_KVM 2
#define VIRTUALIZATION_QEMU 3
#define VIRTUALIZATION_VMWARE 4
#define VIRTUALIZATION_MICROSOFT 5
#define VIRTUALIZATION_BHYVE 6
#define VIRTUALIZATION_QNX 7
#define VIRTUALIZATION_VM_OTHER 8

#define ARRAY_SIZE(a) (sizeof(a)/sizeof(a[0]))

static int detect_vm_cpuid(void)
{
	/* CPUID is an x86 specific interface. */
#if defined(__i386__) || defined(__x86_64__)

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
#endif
	printf("No virtualization found in CPUID\n");

	return VIRTUALIZATION_NONE;
}

