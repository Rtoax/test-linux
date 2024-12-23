#include <net/if.h>
#include <stdio.h>
#include <stdlib.h>


int main(void)
{
	struct if_nameindex *head, *ifni;

	head = if_nameindex();

	ifni = head;
	if (head == NULL) {
		perror("if_nameindex");
		exit(1);
	}

	system("ip address | grep ^[0-9]");

	printf("----------\n");

	while (ifni->if_index != 0) {
		printf("interface %d: %s\n", ifni->if_index, ifni->if_name);
		ifni++;
	}

	printf("----------\n");

	for (ifni = head; !(ifni->if_index == 0 && ifni->if_name == NULL); ifni++)
		printf("interface %u: %s\n", ifni->if_index, ifni->if_name);

	if_freenameindex(head);

	return 0;
}
