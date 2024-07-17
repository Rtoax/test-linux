#include <stdio.h>
#include <netdb.h>

int main(void)
{
	int err;

	printf("%s\n", hstrerror(h_errno));

	for (err = 0; err < 6; err++) {
		printf("%d: %s\n", err, hstrerror(err));
	}
	return 0;
}
