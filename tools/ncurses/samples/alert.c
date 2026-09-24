#include <ncurses.h>
#include <panel.h>
#include <stdlib.h>
#include <string.h>

void show_alert(const char *title, const char *message)
{
	int height = 7;
	int width = 40;
	int starty = (LINES - height) / 2;
	int startx = (COLS - width) / 2;

	WINDOW *alert_win = newwin(height, width, starty, startx);
	if (!alert_win) {
		endwin();
		fprintf(stderr, "newwin failed\n");
		exit(1);
	}

	if (has_colors()) {
		init_pair(1, COLOR_WHITE, COLOR_RED);
		wbkgd(alert_win, COLOR_PAIR(1));
	}

	box(alert_win, 0, 0);
	mvwprintw(alert_win, 0, 2, "[ %s ]", title);

	int msg_x = (width - strlen(message)) / 2;
	mvwprintw(alert_win, height / 2, msg_x, "%s", message);

	mvwprintw(alert_win, height - 2, (width - 18) / 2,
		  "Press any key to continue...");

	PANEL *alert_panel = new_panel(alert_win);
	top_panel(alert_panel);

	update_panels();
	doupdate();

	napms(1000);

	del_panel(alert_panel);
	delwin(alert_win);

	update_panels();
	doupdate();
}

int main(void)
{
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, TRUE);

	if (has_colors()) {
		start_color();
	}

	mvprintw(2, 2, "This is main window");
	mvprintw(4, 2, "System running...");

	WINDOW *bg_win = newwin(10, 30, 8, 2);
	box(bg_win, 0, 0);
	mvwprintw(bg_win, 1, 1, "Back window B");

	refresh();
	wrefresh(bg_win);

	napms(1000);

	show_alert("WARNING", "Disk space low");

	mvprintw(LINES - 2, 2, "Warning cleared");
	refresh();

	napms(1000);

	delwin(bg_win);
	endwin();
	return 0;
}
