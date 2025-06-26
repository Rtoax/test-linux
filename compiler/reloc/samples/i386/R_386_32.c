/**
 * R_X86_64_64
 *
 * value = 1, field = word64, calculation = S + A
 */
#include "compiler.h"

/**
 * s1 ~ s7 are R_X86_64_64 in ELF 64-bit LSB relocatable
 */
const char *s1 = "Hello";
const char *s2 = "Hello";
const char *s3 = "Hello2";
const char *s4 = "Hello2";
const char *s5 = "Hello2";
char *s6 = "Hello2";
static char __unused *s7 = "Hello2";

int main(void)
{
	return 0;
}
