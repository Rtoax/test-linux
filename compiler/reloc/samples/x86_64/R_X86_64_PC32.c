int gi = 0;	/* .bss */
int gii = 1;	/* .data */

/* R_X86_64_PC32 */
int foo(void)
{
	gi = 10;	/* R_X86_64_PC32 */
	return 0;
}

/* R_X86_64_PC32 */
int bar(void)
{
	gii = 20;	/* R_X86_64_PC32 */
	return 0;
}
