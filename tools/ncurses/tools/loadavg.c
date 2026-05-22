// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao
/**
 * Plot and display a loadavg graph of 1, 5, 15 minutes in the Linux terminal
 * with minimal dependencies.
 *
 * see also test-linux/scripts/loadavg.sh
 */
#include <ncurses.h>

int main(void)
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);

	/* do more/something */

	endwin();
	return 0;
}
