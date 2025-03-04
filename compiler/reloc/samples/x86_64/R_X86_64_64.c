/**
 * R_X86_64_64
 *
 * value = 1, field = word64, calculation = S + A
 */

/* s1 ~ s8 are R_X86_64_64 in ELF 64-bit LSB relocatable */
const char *s1 = "Hello";	/* .data, GLOBAL */	/* .rela.data */
const char *s2 = "Hello";	/* .data, GLOBAL */	/* .rela.data */
const char *s3 = "Hello2";	/* .data, GLOBAL */	/* .rela.data */
const char *s4 = "Hello2";	/* .data, GLOBAL */	/* .rela.data */
const char *s5 = "Hello2";	/* .data, GLOBAL */	/* .rela.data */
char *s6 = "Hello2";		/* .data, GLOBAL */	/* .rela.data */
static char *s7 = "Hello2";	/* .data, LOCAL */	/* .rela.data */
char *const s8 = "Hello2";	/* .rodata, GLOBAL */	/* .rela.rodata */

/* main is R_X86_64_PC32 in ELF 64-bit LSB relocatable */
int main(void)	/* .rela.eh_frame */
{
	return 0;
}
