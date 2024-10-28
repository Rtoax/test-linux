#include <stddef.h>

static long sil = 1;
static long *psl;

int main(void)
{
	/**
	 * psl is R_X86_64_PC32
	 * &sil is R_X86_64_32S in ELF 64-bit LSB relocatable
	 */
	psl = NULL;
	psl = &sil;

	return 0;
}
