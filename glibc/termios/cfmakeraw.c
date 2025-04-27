#include <stdio.h>
#include <termios.h>
#include "termios_helpers.h"

int main(void)
{
	struct termios t;

	cfmakeraw(&t);

	print_termios(&t);

	return 0;
}
