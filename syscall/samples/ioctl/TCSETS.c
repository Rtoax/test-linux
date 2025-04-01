#include <stdio.h>
#include <sys/ioctl.h>
#include <termios.h>

int main(void)
{
	struct termios term;

	ioctl(fileno(stdin), TCGETS, &term);

	printf("Input flags: %x\n", term.c_iflag);
	printf("Output flags: %x\n", term.c_oflag);
	printf("Control flags: %x\n", term.c_cflag);
	printf("Local flags: %x\n", term.c_lflag);
	printf("Line discipline: %d\n", term.c_line);

	/* TODO: test TCSETS */

	return 0;
}
