#include <stdio.h>
#include <termios.h>

int set_istrip(int desc, int value)
{
	int result;
	struct termios settings;

	result = tcgetattr(desc, &settings);
	if (result < 0) {
		perror ("error in tcgetattr");
		return 0;
	}
	/* Strip off eighth bit */
	settings.c_iflag &= ~ISTRIP;
	if (value)
		settings.c_iflag |= ISTRIP;
	result = tcsetattr(desc, TCSANOW, &settings);
	if (result < 0) {
		perror("error in tcsetattr");
		return 0;
	}
	return 1;
}

int main(void)
{
	int i;

	set_istrip(fileno(stdin), 1);

	for (i = 0; i < 5; i++) {
		char x = getchar();
		printf("[%c] ", x);
	}

	return 0;
}
