#include <stdio.h>
#include <elf.h>

int main(void)
{
#define P(v) printf("%-48s : %d\n", #v, v);
        P(R_X86_64_NONE);
        P(R_X86_64_64);
        P(R_X86_64_PC32);
        P(R_X86_64_GOT32);
        P(R_X86_64_PLT32);
        P(R_X86_64_COPY);
        P(R_X86_64_GLOB_DAT);
        P(R_X86_64_JUMP_SLOT);
        P(R_X86_64_RELATIVE);
        P(R_X86_64_GOTPCREL);
        P(R_X86_64_32);
        P(R_X86_64_32S);
        P(R_X86_64_16);
        P(R_X86_64_PC16);
        P(R_X86_64_8);
        P(R_X86_64_PC8);
        P(R_X86_64_DTPMOD64);
        P(R_X86_64_DTPOFF64);
        P(R_X86_64_TPOFF64);
        P(R_X86_64_TLSGD);
        P(R_X86_64_TLSLD);
        P(R_X86_64_DTPOFF32);
        P(R_X86_64_GOTTPOFF);
        P(R_X86_64_TPOFF32);
        P(R_X86_64_PC64);
        P(R_X86_64_GOTOFF64);
        P(R_X86_64_GOTPC32);
        P(R_X86_64_GOT64);
        P(R_X86_64_GOTPCREL64);
        P(R_X86_64_GOTPC64);
        P(R_X86_64_GOTPLT64);
        P(R_X86_64_PLTOFF64);
        P(R_X86_64_SIZE32);
        P(R_X86_64_SIZE64);
        P(R_X86_64_GOTPC32_TLSDESC);
        P(R_X86_64_TLSDESC_CALL);
        P(R_X86_64_TLSDESC);
        P(R_X86_64_IRELATIVE);
        P(R_X86_64_RELATIVE64);
        P(R_X86_64_GOTPCRELX);
        P(R_X86_64_REX_GOTPCRELX);
        P(R_X86_64_NUM);
#if R_X86_64_NUM - 1 != R_X86_64_REX_GOTPCRELX
# error Found new R_X86_64_ in /usr/include/elf.h
#endif
#undef P
	return 0;
}
