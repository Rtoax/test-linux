/**
 * R_X86_64_32S
 *
 * R_X86_64_32S cannot be used in position independent executables.
 * e.g. done with gcc -pie, otherwise link fails with:
 * relocation R_X86_64_32S against `.text' can not be used when making a PIE object; recompile with -fPIC
 */

#include <stddef.h>

#define RODATA_1	"Hello"

static long sli = 1;
static long *psl;

const long gcl1 = 0xFFFFFFFF;
const long gcl2 = 0x11111111;

int main(void)
{
	/**
	 * s1 and s2 are R_X86_64_32S in ELF 64-bit LSB relocatable
	 */
	const char *s1 = RODATA_1;
	const char *s2 = RODATA_1;

	/**
	 * psl is R_X86_64_PC32
	 * &sli is R_X86_64_32S in ELF 64-bit LSB relocatable
	 */
	psl = NULL;
	psl = &sli;

	/**
	 * gcl1 and gcl2 are R_X86_64_32S in ELF 64-bit LSB relocatable
	 */
	const long *pl1 = &gcl1;
	const long *pl2 = &gcl2;

	return 0;
}
