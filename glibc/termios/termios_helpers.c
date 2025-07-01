// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <stdio.h>
#include "termios_helpers.h"

int print_termios(struct termios *t)
{
	printf("%2d:%4d:%c\n", VSTART, t->c_cc[VSTART], (char)t->c_cc[VSTART]);
	printf("%2d:%4d:%c\n", VSTOP, t->c_cc[VSTOP], (char)t->c_cc[VSTOP]);

	printf("%2d:%4d:%c\n", VINTR, t->c_cc[VINTR], (char)t->c_cc[VINTR]);
	printf("%2d:%4d:%c\n", VQUIT, t->c_cc[VQUIT], (char)t->c_cc[VQUIT]);
	printf("%2d:%4d:%c\n", VSUSP, t->c_cc[VSUSP], (char)t->c_cc[VSUSP]);

#ifdef VDSUSP
	printf("%2d:%4d:%c\n", VDSUSP, t->c_cc[VDSUSP], (char)t->c_cc[VDSUSP]);
#endif

	printf("%2d:%4d:%c\n", VEOF, t->c_cc[VEOF], (char)t->c_cc[VEOF]);
	printf("%2d:%4d:%c\n", VEOL, t->c_cc[VEOL], (char)t->c_cc[VEOL]);
	printf("%2d:%4d:%c\n", VEOL2, t->c_cc[VEOL2], (char)t->c_cc[VEOL2]);
	printf("%2d:%4d:%c\n", VERASE, t->c_cc[VERASE], (char)t->c_cc[VERASE]);
	printf("%2d:%4d:%c\n", VWERASE, t->c_cc[VWERASE], (char)t->c_cc[VWERASE]);
	printf("%2d:%4d:%c\n", VKILL, t->c_cc[VKILL], (char)t->c_cc[VKILL]);
	printf("%2d:%4d:%c\n", VREPRINT, t->c_cc[VREPRINT], (char)t->c_cc[VREPRINT]);

	return 0;
}
