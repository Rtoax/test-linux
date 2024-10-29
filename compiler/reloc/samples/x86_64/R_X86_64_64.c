/**
 * R_X86_64_64
 *
 * value = 1, field = word64, calculation = S + A
 */

/**
 * s1 ~ s8 are R_X86_64_64 in ELF 64-bit LSB relocatable
 */
const char *s1 = "Hello";	/* .data, GLOBAL */
const char *s2 = "Hello";	/* .data, GLOBAL */
const char *s3 = "Hello2";	/* .data, GLOBAL */
const char *s4 = "Hello2";	/* .data, GLOBAL */
const char *s5 = "Hello2";	/* .data, GLOBAL */
char *s6 = "Hello2";		/* .data, GLOBAL */
static char *s7 = "Hello2";	/* .data, LOCAL */
char *const s8 = "Hello2";	/* .rodata, GLOBAL */

int main(void)
{
	return 0;
}
