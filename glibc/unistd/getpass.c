#include <termios.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>
#include <string.h>
#include <malloc.h>
#include <stdlib.h>

int main(void)
{
	char prompt[256];

	memset(prompt, 0, sizeof(prompt));
	sprintf(prompt, "password: ");
	char *ret = malloc(256);

	unsigned int try_times = 0;
	ret = getpass(prompt);
	while (strncmp(ret, "rong ", 5) != 0) {
		try_times++;
		printf(" try again: ");
		if (try_times > 2) {
			printf("Good bye.\n");
			exit(1);
		}
		ret = getpass(prompt);
	}

	printf("%s\n", ret);

	return 0;
}

