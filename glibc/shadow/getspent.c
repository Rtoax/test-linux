#include <stdio.h>
#include <stdlib.h>
#include <shadow.h>
#include <errno.h>

#include "shadow_helpers.h"


int main(int argc, char *argv[])
{
	struct spwd *spwd = getspent();
	if (!spwd) {
		/* FIXME: getspent should set errno??? */
		errno = EPERM;
		fprintf(stderr, "getspent: %m\n");
		exit(EXIT_FAILURE);
	}

	display_spwd(spwd);

	return 0;
}

