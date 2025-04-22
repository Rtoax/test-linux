/**
 * R_X86_64_64 (like aarch64's R_AARCH64_ABS64)
 *
 * value = 1, field = word64, calculation = S + A
 */
#include <stddef.h>

/**
 * in ELF 64-bit LSB relocatable:
 * s1 ~ s9 and pi1 ~ pi2 are R_X86_64_64
 */

/* section ".rodata" */
#define RODATA_1	"Hello1"
#define RODATA_2	"Hello2"
#define RODATA_3	"Hello3"
#define RODATA_4	"Hello4"

/* section ".data" */
static int arr_i[] = { 1, 2, 3, 4 };

/**
 * in ELF 64-bit LSB relocatable:
 * s1 ~ s7 in ".rela.data" for non-pie, ".rela.data.rel.local" for pie
 */
const char *s1 = RODATA_1;	/* .data, GLOBAL */
const char *s2 = RODATA_1;	/* .data, GLOBAL */
const char *s3 = RODATA_2;	/* .data, GLOBAL */
const char *s4 = RODATA_2;	/* .data, GLOBAL */
const char *s5 = RODATA_2;	/* .data, GLOBAL */
char *s6 = RODATA_2;		/* .data, GLOBAL */
static char *s7 = RODATA_2;	/* .data, LOCAL */

/**
 * in ELF 64-bit LSB relocatable:
 * s8 ~ s9 in ".rela.redata" for non-pie, ".rela.data.rel.ro.local" for pie
 */
char *const s8 = RODATA_3;	/* .rodata, GLOBAL */
char *const s9 = RODATA_4;	/* .rodata, GLOBAL */

const char *s10 = NULL;

/**
 * in ELF 64-bit LSB relocatable:
 * pi1 ~ pi3 in ".rela.redata" for non-pie, ".rela.data.rel.ro.local" for pie
 */
int *pi1 = arr_i;
int *pi2 = arr_i + 1;
int *pi3 = arr_i + 2;

/**
 * in ELF 64-bit LSB relocatable:
 * main is R_X86_64_PC32
 */
int main(void)	/* .rela.eh_frame */
{
	char local_s2[] = RODATA_1;	/* not rela */
#if 0
	/**
	 * in ELF 64-bit LSB relocatable:
	 * ls1 ~ ls4 and lpi1,lpi2 are R_X86_64_32S
	 */
	const char *ls1 = RODATA_1;
	const char *ls2 = RODATA_2;
	const char *ls3 = RODATA_3;
	char *ls4 = RODATA_3;
	int *lpi1 = arr_i;
	int *lpi2 = arr_i + 1;
#endif
	return 0;
}
