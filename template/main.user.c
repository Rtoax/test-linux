// SPDX-License-Identifier: GPL-3.0
#include <stdio.h>
#include "main.h"

int main(int argc, char *argv[])
{
#if !defined(_MAIN_USER)
# error "Must define _MAIN_USER"
#endif
#if !defined(CONFIG_MMU)
# warning "Kernel not define CONFIG_MMU"
#endif
#if !defined(HAVE_PRINTF)
# error "Not found printf(3)"
#else
	printf("Hello\n");
#endif
	return 0;
}
