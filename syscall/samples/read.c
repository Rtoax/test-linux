#include <stdio.h>
#include <unistd.h>

int main(void)
{
	ssize_t n;
	char buf[64];

	while (1) {
		n = read(0, buf, sizeof(buf));
		if (n == -1) {
			fprintf(stderr, "%m\n");
			continue;
		}
		printf("%c", buf[0]);
	}

	return 0;
}
