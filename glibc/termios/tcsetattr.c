#include <stdio.h>
#include <unistd.h>
#include <termios.h>

int main(int argc, char *argv[])
{
	int i;
	struct termios old, new;

	tcgetattr(STDIN_FILENO, &old);

	new = old;
	/* disable line buffering and feedback */
	new.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	tcsetattr(STDIN_FILENO, TCSANOW, &new);

	printf("Reading 5 characters without local echo...\n");
	for (i = 0; i < 5; i++) {
		char x = getchar();
		printf("[%c] ", x);
	}
	printf("\nRestoring terminal config\n");
	tcsetattr(STDIN_FILENO, TCSANOW, &old);

	return 0;
}
