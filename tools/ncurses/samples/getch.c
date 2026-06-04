#include <ncurses.h>

#ifdef TEST_MOUSE
void handle_mouse_event(void)
{
	MEVENT event;
	if (getmouse(&event) != OK)
		return;

	move(7, 0);
	clrtoeol();
	move(8, 0);
	clrtoeol();

	if (event.bstate & BUTTON1_CLICKED) {
		mvprintw(7, 0, "left row=%d, col=%d", event.y, event.x);
	} else if (event.bstate & BUTTON3_CLICKED) {
		mvprintw(7, 0, "right click");
	} else if (event.bstate & BUTTON4_PRESSED) {
		mvprintw(7, 0, "scroll up");
	} else if (event.bstate & BUTTON5_PRESSED) {
		mvprintw(7, 0, "scroll down");
	} else if (event.bstate & REPORT_MOUSE_POSITION) {
		mvprintw(7, 0, "move row=%d, col=%d", event.y, event.x);
	}

	refresh();
}
#endif

int main(void)
{
	int err = 0;

	initscr();
	cbreak();
	noecho();
	curs_set(0);

	keypad(stdscr, TRUE);
	/**
	 * nodelay configures the input character reading function to be
	 * non-blocking for window win.
	 */
	nodelay(stdscr, TRUE);

#ifdef TEST_MOUSE
#if 0 /* TODO: why failed? */
	if (has_mouse() != TRUE) {
		fprintf(stderr, "Not found mouse.\n");
		err = 1;
		goto end;
	}
#endif
	mmask_t mask = BUTTON1_CLICKED | BUTTON3_CLICKED | BUTTON4_PRESSED |
		       BUTTON5_PRESSED | REPORT_MOUSE_POSITION;
	mmask_t oldmask;
	if (mousemask(mask, &oldmask) == 0) {
		fprintf(stderr, "Not support mouse event.\n");
		err = 2;
		goto end;
	}
#endif

	while (1) {
		/* actually, getch() read from stdin */
		int c = getch();
		if (c != ERR) {
			switch (c) {
#ifdef TEST_MOUSE
			case KEY_MOUSE:
				handle_mouse_event();
				break;
#endif
			case KEY_LEFT:
				printw("KEY_LEFT %d\n", c);
				break;
			default:
				printw("getch = '%c' %d\n", c, c);
				break;
			}
			refresh();
			switch (c) {
			case 'q':
				goto end;
				break;
			}
		}
	}

end:
	refresh();
	endwin();
	return err;
}
