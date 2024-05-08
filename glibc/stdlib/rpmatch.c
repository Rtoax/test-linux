#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <malloc.h>
#include <locale.h>
#include <libintl.h>

void hint(void)
{
	fputs(gettext("Do you really want to do this? [Y/N]: "), stdout);
	fflush(stdout);
}

int main(void)
{
	char *line = malloc(256);
	size_t len;

	/* Use a safe default. */
	bool doit = false;

	/* Prepare the getline call. */
	line = NULL;
	len = 0;

	hint();

	while (getline(&line, &len, stdin) >= 0) {
		/* Check the response. */
		int res = rpmatch(line);
		if (res >= 0) {
			/* We got a defnitive answer. */
			if (res > 0)
				doit = true;
			break;
		}
		hint();
	}
	/* Free what getline allocated. */
	free(line);

	printf("%s\n", doit == true ? "Yes, you select YES" : "No, You select NO");

	return 0;
}
