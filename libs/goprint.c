// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <stdlib.h>
#include "gotoxy.h"

#ifdef TEST_MAIN
int main(int argc, char *argv[])
{
	if (argc < 4) {
		fprintf(stderr, "ERROR: %s [x] [y] [str]\n", argv[0]);
		exit(1);
	}
	gotoxy(atoi(argv[1]), atoi(argv[2]));
	printf("%s", argv[3]);
	return 0;
}
#endif
