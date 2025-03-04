#include <stdio.h>
#include <elf.h>

int main(void)
{
#define RELOC_AARCH64(r) printf("%-48s : 0x%x (%d)\n", #r, r, r);
#define RELOC_X86_64(r) printf("%-48s : 0x%x (%d)\n", #r, r, r);
#define RELOC_I386(r) printf("%-48s : 0x%x (%d)\n", #r, r, r);
#include "relocs-gen.h"
#undef RELOC_AARCH64
#undef RELOC_I386
#undef RELOC_X86_64
	return 0;
}
