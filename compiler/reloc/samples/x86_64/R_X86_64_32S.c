/**
 * R_X86_64_32S
 *
 * R_X86_64_32S cannot be used in position independent executables.
 * e.g. done with gcc -pie, otherwise link fails with:
 * relocation R_X86_64_32S against `.text' can not be used when making a PIE object; recompile with -fPIC
 */

#include <stddef.h>

static long sil = 1;
static long *psl;

const long gcl = 0xFFFFFFFF;

int main(void)
{
	/**
	 * s1 and s2 are R_X86_64_32S in ELF 64-bit LSB relocatable
	 */
	const char *s1 = "Hello";
	const char *s2 = "Hello";

	/**
	 * psl is R_X86_64_PC32
	 * &sil is R_X86_64_32S in ELF 64-bit LSB relocatable
	 */
	psl = NULL;
	psl = &sil;

	/**
	 * gcl is R_X86_64_32S in ELF 64-bit LSB relocatable
	 */
	const long *pl = &gcl;

	return 0;
}
