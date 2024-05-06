#include <stdio.h>
#include <stdlib.h>
#include <net/if.h>

int main(int argc, char *argv[])
{
	char buf[128];
	char *if_name;
	int idx = 1;

	if_name = if_indextoname(idx, buf);
	if (if_name == NULL) {
		perror("if_nameindex");
		exit(1);
	}

	printf("interface %d: %s\n", idx, if_name);

	return 0;
}
