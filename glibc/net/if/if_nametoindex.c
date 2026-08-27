#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	if (argc < 2) {
		printf("error: Usage: %s [interface name]\n", argv[0]);
		exit(1);
	}

	for (int i = 1; i < argc; i++) {
		unsigned int if_index = if_nametoindex(argv[i]);
		if (if_index == 0) {
			perror("if_nametoindex");
			exit(1);
		}

		printf("interface %s: %d\n", argv[i], if_index);
	}

	return 0;
}
