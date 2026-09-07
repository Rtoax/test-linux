// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
#include <errno.h>
#include <stdio.h>
#include <utmp.h>
#include "utmp_helpers.h"

int print_utmp(struct utmp *ut)
{
	if (!ut) {
		fprintf(stderr, "try print NULL utmp.\n");
		return -EINVAL;
	}

	printf("ut_type: %d\n", ut->ut_type);
	printf("ut_user: %s\n", ut->ut_user);
	printf("ut_line: %s\n", ut->ut_line);
	printf("ut_id: %s\n", ut->ut_id);
	printf("ut_host: %s\n", ut->ut_host);
	return 0;
}

