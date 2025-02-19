#include <stdio.h>
#include <unistd.h>
#include <termios.h>

#include "../../libs/gotoxy.h"

/* Function to set terminal to raw mode */
void set_raw_mode(struct termios *old_termios)
{
	struct termios new_termios;
	tcgetattr(STDIN_FILENO, old_termios);
	new_termios = *old_termios;
	cfmakeraw(&new_termios);
	tcsetattr(STDIN_FILENO, TCSANOW, &new_termios);
}

/* Function to restore terminal to original mode */
void restore_terminal_mode(struct termios *old_termios)
{
	tcsetattr(STDIN_FILENO, TCSANOW, old_termios);
}

/* Function to get cursor position */
void get_cursor_position(unsigned short *rows, unsigned short *cols)
{
	char buf[32];
	unsigned int i = 0;
	struct termios old_termios;

	/* Set terminal to raw mode */
	set_raw_mode(&old_termios);

	/* Send the DSR (Device Status Report) command */
	printf("\033[6n");
	fflush(stdout);

	/* Read the response: ESC [ rows ; cols R */
	while (i < sizeof(buf) - 1) {
		if (read(STDIN_FILENO, buf + i, 1) != 1) {
			break;
		}
		if (buf[i] == 'R') {
			break;
		}
		i++;
	}
	buf[i] = '\0';

	/* Restore the original terminal mode */
	restore_terminal_mode(&old_termios);

	/* Parse the response */
	if (buf[0] == '\033' && buf[1] == '[') {
		sscanf(buf + 2, "%hd;%hd", rows, cols);
	}
}

int main(void)
{
	unsigned short rows, cols;

	getwinsz(&rows, &cols);

	printf("Win size: %d, %d\n", rows, cols);

	gotoxy(cols / 2, rows / 2);

	get_cursor_position(&rows, &cols);

	printf("Cursor Position: %d, %d\n", rows, cols);

	return 0;
}
