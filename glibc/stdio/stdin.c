#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void)
{
	char ch;

	while (1) {
		read(STDIN_FILENO, &ch, 1);
		printf("ch = %c\n", ch);
	}
	return 0;
}
