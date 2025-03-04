/**
 * R_X86_64_64
 *
 * value = 1, field = word64, calculation = S + A
 */

/* s1 ~ s8 are R_X86_64_64 in ELF 64-bit LSB relocatable */

/* s1 ~ s7 in .rela.data for non-pie, .rela.data.rel.local for pie */
const char *s1 = "Hello";	/* .data, GLOBAL */
const char *s2 = "Hello";	/* .data, GLOBAL */
const char *s3 = "Hello2";	/* .data, GLOBAL */
const char *s4 = "Hello2";	/* .data, GLOBAL */
const char *s5 = "Hello2";	/* .data, GLOBAL */
char *s6 = "Hello2";		/* .data, GLOBAL */
static char *s7 = "Hello2";	/* .data, LOCAL */

/* s8 in .rela.redata for non-pie, .rela.data.rel.ro.local for pie */
char *const s8 = "Hello2";	/* .rodata, GLOBAL */

/* main is R_X86_64_PC32 in ELF 64-bit LSB relocatable */
int main(void)	/* .rela.eh_frame */
{
	return 0;
}
