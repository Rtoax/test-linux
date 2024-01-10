#include <stdio.h>
#include <unistd.h>

#define PAGE_SIZE	getpagesize()
#define ELF_MIN_ALIGN	PAGE_SIZE

#define ELF_PAGESTART(_v) ((_v) & ~(unsigned long)(ELF_MIN_ALIGN-1))
#define ELF_PAGEOFFSET(_v) ((_v) & (ELF_MIN_ALIGN-1))
#define ELF_PAGEALIGN(_v) (((_v) + ELF_MIN_ALIGN - 1) & ~(ELF_MIN_ALIGN - 1))

int main(void)
{
#define V(v) do {	\
		printf("%-32s ", #v);	\
		printf("%016lx (%-16ld)\n", v, v);	\
	} while(0)

	V(ELF_PAGESTART(0xffff123UL));
	V(ELF_PAGESTART(-0x123UL));
	V(ELF_PAGEOFFSET(0xffff123UL));
	V(ELF_PAGEALIGN(0xffff123UL));
	V(ELF_PAGEALIGN(0xffff000UL));

#undef V
	return 0;
}
