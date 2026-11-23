/**
 * Musl libc not supply __GNUC_PREREQ().
 */
#ifndef __GNUC__
#error Not define __GNUC__
#endif

#ifdef __GNUC_PREREQ
#error Musl libc defined __GNUC_PREREQ()
#endif

int main(void)
{
	return 0;
}
