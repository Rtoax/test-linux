#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	int id = gethostid();

	int ret = sethostid(id);
	if (ret == -1) {
		fprintf(stderr, "sethostid %m\n");
		return -errno;
	}

	printf("%d. ret = %d\n", id, ret);

	return 0;
}
