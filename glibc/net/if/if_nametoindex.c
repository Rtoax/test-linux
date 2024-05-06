#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("error: Usage: %s [interface name]\n", argv[0]);
		exit(1);
	}

	unsigned int if_index = if_nametoindex(argv[1]);
	if (if_index == 0) {
		perror("if_nametoindex");
		exit(1);
	}

	printf("interface %s: %d\n", argv[1], if_index);

	return 0;
}
