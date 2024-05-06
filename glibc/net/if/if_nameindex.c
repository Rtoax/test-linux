#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	struct if_nameindex *head, *ifni;

	ifni = if_nameindex();

	head = ifni;
	if (head == NULL) {
		perror("if_nameindex");
		exit(1);
	}

	while (ifni->if_index != 0) {
		printf("interface %d: %s\n", ifni->if_index, ifni->if_name);
		ifni++;
	}

	if_freenameindex(head);

	return 0;
}
