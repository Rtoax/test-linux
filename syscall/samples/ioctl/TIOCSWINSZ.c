/**
 * ioctl(fd, TIOCGWINSZ, sz)
 * ioctl(fd, TIOCSWINSZ, sz)
 *
 * see also ncurses's getmaxyx(), getmaxy(), getmaxx().
 */
#include <stdio.h>
#include <signal.h>
#include <sys/ioctl.h>

/**
 * Window size changed
 */
void sig_handler(int signum)
{
	switch (signum) {
	case SIGWINCH:
		printf("Get signal SIGWINCH.\n");
		break;
	}
}

int main(void)
{
	struct winsize sz;

	signal(SIGWINCH, sig_handler);

	ioctl(fileno(stdin), TIOCGWINSZ, &sz);

	sz.ws_col /= 2;
	sz.ws_row /= 2;

	/* Set window size */
	ioctl(fileno(stdin), TIOCSWINSZ, &sz);

#if defined(__sw_64__)
	printf("TIOCSWINSZ = %#08lx\n", TIOCSWINSZ);
#else
	printf("TIOCSWINSZ = %#08x\n", TIOCSWINSZ);
#endif

	printf("%i, %i, %i, %i\n", sz.ws_col, sz.ws_row, sz.ws_xpixel,
	       sz.ws_ypixel);

	pause();

	return 0;
}
