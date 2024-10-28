/**
 * R_X86_64_PC64: value = 24, field = word64, calculation = S + A - P
 * R_X86_64_PC32: value = 2,  field = word32, calculation = S + A - P
 * R_X86_64_PC16: value = 13, field = word16, calculation = S + A - P
 * R_X86_64_PC8:  value = 15, field = word8,  calculation = S + A - P
 */

#include <stddef.h>
#include <stdint.h>

int8_t gi8 = 0;	/* .bss, GLOBAL */

int32_t gi = 0;	/* .bss, GLOBAL */
int32_t gii = 1;	/* .data, GLOBAL */

int64_t gl = 0;	/* .bss, GLOBAL */
int64_t *pgl = NULL;	/* .bss, GLOBAL */

static int32_t si1 = 0;	/* .bss, LOCAL */
static int32_t si2 = 0;	/* .bss, LOCAL */
static int32_t sii = 1;	/* .data, LOCAL */

static int32_t sl = 0;	/* .bss, LOCAL */

/* R_X86_64_PC32 */
void foo(void)
{
	gi8 = 10;	/* R_X86_64_PC32 */

	gi = 10;	/* R_X86_64_PC32 */
	si1 = 10;	/* R_X86_64_PC32 */
	si2 = 10;	/* R_X86_64_PC32 */

	gl = 10;	/* R_X86_64_PC32 */
	pgl = NULL;	/* R_X86_64_PC32 */

	sl = 10;	/* R_X86_64_PC32 */
}

/* R_X86_64_PC32 */
void bar(void)
{
	gii = 20;	/* R_X86_64_PC32 */
	sii = 20;	/* R_X86_64_PC32 */
}

/* R_X86_64_PC32 */
int main(void)
{
	return 0;
}
