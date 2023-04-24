#include <stdio.h>
#include <stdint.h>
//#include <cpuid.h>


static inline void
cpuid(unsigned int op, unsigned int *eax, unsigned int *ebx, unsigned int *ecx,
	  unsigned int *edx)
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

void vendor_id(void)
{
	int	cpuid_level = 0;
	char x86_vendor_id[16] = {0};

	cpuid(0x00000000,
		(unsigned int *)&cpuid_level,
		(unsigned int *)&x86_vendor_id[0],
		(unsigned int *)&x86_vendor_id[8],
		(unsigned int *)&x86_vendor_id[4]);

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

void cpu_address_sizes()
{
	unsigned int x86_virt_bits, x86_phys_bits;
	unsigned int eax, ebx, ecx, edx;

	cpuid(0x80000008, &eax, &ebx, &ecx, &edx);

	x86_virt_bits = (eax >> 8) & 0xff;
	x86_phys_bits = eax & 0xff;

	printf("Address size: %d bits physical, %d bits virtual.\n",
		x86_phys_bits, x86_virt_bits);
}

int main(int argc, char *argv[])
{
	vendor_id();
	family_model();
	model_name();
	cpu_address_sizes();

	return 0;
}

