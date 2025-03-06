/**
 * R_X86_64_PC64: value = 24, field = word64, calculation = S + A - P
 * R_X86_64_PC32: value = 2,  field = word32, calculation = S + A - P
 * R_X86_64_PC16: value = 13, field = word16, calculation = S + A - P
 * R_X86_64_PC8:  value = 15, field = word8,  calculation = S + A - P
 */

#include <stddef.h>
#include <stdint.h>

int8_t gi8 = 0;	/* .bss, GLOBAL */
int16_t gi16 = 0;	/* .bss, GLOBAL */
int32_t gi32 = 0;	/* .bss, GLOBAL */
int64_t gi64 = 0;	/* .bss, GLOBAL */
int64_t *pgi64 = NULL;	/* .bss, GLOBAL */

int8_t gi8i = 1;	/* .data, GLOBAL */
int32_t gi32i = 1;	/* .data, GLOBAL */

static int32_t si32 = 0;	/* .bss, LOCAL */
static int64_t si64 = 0;	/* .bss, LOCAL */

static int32_t si32i = 1;	/* .data, LOCAL */
static int64_t si64i = 1;	/* .data, LOCAL */

int arr_i[] = {1, 2, 3, 4};

/* foo is R_X86_64_PC32 */
void foo(void)
{
	gi8 = 10;	/* R_X86_64_PC32 */
	gi16 = 10;	/* R_X86_64_PC32 */
	gi32 = 10;	/* R_X86_64_PC32 */
	gi64 = 10;	/* R_X86_64_PC32 */

	si32 = 10;	/* R_X86_64_PC32 */

	pgi64 = NULL;	/* R_X86_64_PC32 */

	si64 = 10;	/* R_X86_64_PC32 */
}
void foo_alias1(void) __attribute__((alias("foo")));
void foo_alias2(void) __attribute__((alias("foo")));

/* bar is R_X86_64_PC32 */
void bar(void)
{
	gi8i = 20;	/* R_X86_64_PC32 */
	gi32i = 20;	/* R_X86_64_PC32 */
	si32i = 20;	/* R_X86_64_PC32 */
	si64i = 20;	/* R_X86_64_PC32 */

	arr_i[0] = 1;	/* R_X86_64_PC32 */
	arr_i[1] = 1;	/* R_X86_64_PC32 */
	arr_i[2] = 1;	/* R_X86_64_PC32 */
	arr_i[3] = 1;	/* R_X86_64_PC32 */
}

/* main is R_X86_64_PC32 */
int main(void)
{
	return 0;
}
