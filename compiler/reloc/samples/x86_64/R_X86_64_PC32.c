int gi = 0;	/* .bss, GLOBAL */
int gii = 1;	/* .data, GLOBAL */

long gl = 0;	/* .bss, GLOBAL */

static int si1 = 0;	/* .bss, LOCAL */
static int si2 = 0;	/* .bss, LOCAL */
static int sii = 1;	/* .data, LOCAL */

static int sl = 0;	/* .bss, LOCAL */

/* R_X86_64_PC32 */
int foo(void)
{
	gi = 10;	/* R_X86_64_PC32 */
	si1 = 10;	/* R_X86_64_PC32 */
	si2 = 10;	/* R_X86_64_PC32 */

	gl = 10;	/* R_X86_64_PC32 */
	sl = 10;	/* R_X86_64_PC32 */
	return 0;
}

/* R_X86_64_PC32 */
int bar(void)
{
	gii = 20;	/* R_X86_64_PC32 */
	sii = 20;	/* R_X86_64_PC32 */
	return 0;
}

/* R_X86_64_PC32 */
int main(void)
{
	return 0;
}
