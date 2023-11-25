/**
 * File:
 * Author:
 * Date:
 *
 * Description:
 * Ref:
 */
#include <stdio.h>

int main(int argc, char *argv[])
{
#if !defined(_MAIN_USER)
# error "Must define _MAIN_USER"
#endif
#if !defined(CONFIG_MMU)
# error "Kernel not define CONFIG_MMU"
#endif
	return 0;
}
