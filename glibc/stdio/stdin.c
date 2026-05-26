/**
 * test:
 * $ cat /etc/os-release | ./stdin
 */
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	while (1) {
		char ch = '\0';
		int err = read(STDIN_FILENO, &ch, 1);
		if (err <= 0 || ch == EOF) {
			fprintf(stderr, "read('%c') = %d\n", ch, err);
			break;
		}
		putchar(ch);
	}
	return 0;
}
