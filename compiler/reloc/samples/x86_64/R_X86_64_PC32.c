int gi = 0;	/* .bss, GLOBAL */
int gii = 1;	/* .data, GLOBAL */

static int si = 0;	/* .bss, LOCAL */
static int sii = 1;	/* .data, LOCAL */

/* R_X86_64_PC32 */
int foo(void)
{
	gi = 10;	/* R_X86_64_PC32 */
	si = 10;	/* R_X86_64_PC32 */
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
