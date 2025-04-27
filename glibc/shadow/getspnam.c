#include <stdio.h>
#include <stdlib.h>
#include <shadow.h>
#include <errno.h>

#include "shadow_helpers.h"


int main(int argc, char *argv[])
{
	struct spwd *spwd = getspnam("root");
	if (!spwd) {
		fprintf(stderr, "getspnam: %m\n");
		exit(EXIT_FAILURE);
	}

	display_spwd(spwd);

	return 0;
}

