#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int ret;
	char name[256] = {0};
	char newdomain[] = "localdomain";

	getdomainname(name, sizeof(name));
	printf("%s\n", name);

	ret = setdomainname(newdomain, sizeof(newdomain));
	if (ret == -1) {
		fprintf(stderr, "setdomainname: %m\n");
		return 1;
	}

	getdomainname(name, sizeof(name));
	printf("%s\n", name);

	return 0;
}

