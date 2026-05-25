// SPDX-License-Identifier: GPL-2.0
// Copyright (C) 2026 Rong Tao
/**
 * Plot and display a loadavg graph of 1, 5, 15 minutes in the Linux terminal
 * with minimal dependencies.
 *
 * see also test-linux/scripts/loadavg.sh
 */
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include <unistd.h>

int getload(int *l1, int *l5, int *l15, int scale)
{
	FILE *fp = fopen("/proc/loadavg", "r");
	if (!fp) {
		fprintf(stderr, "open /proc/loadavg failed, %m\n");
		return -errno;
	}

	float load1, load5, load15;
	fscanf(fp, "%f %f %f", &load1, &load5, &load15);

	*l1 = load1 * scale;
	*l5 = load5 * scale;
	*l15 = load15 * scale;

	fclose(fp);
	return 0;
}

void load_window(void)
{
	// TODO
	while (1) {
		int l1, l5, l15;
		getload(&l1, &l5, &l15, 1000);

		printw("%d %d %d\n", l1, l5, l15);
		refresh();
		sleep(1);
	}
}

int main(void)
{
	initscr();
	cbreak();
	noecho();
	curs_set(0);

	load_window();

	endwin();
	return 0;
}
