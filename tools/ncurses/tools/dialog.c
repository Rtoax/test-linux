// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#include <unistd.h>
#include "plot.h"
#include "keyboard.h"
#include "utils.h"
#include "dialog.h"

void new_dialog(struct dialog *d, WINDOW *win)
{
	d->win = win;
	d->panel = new_panel(win);
	top_panel(d->panel);
}

void del_dialog(struct dialog *d)
{
	/* need delete panel first */
	if (d->panel) {
		del_panel(d->panel);
		d->panel = NULL;
	}
	if (d->win) {
		delwin(d->win);
		d->win = NULL;
	}
}

void erase_dialog(struct dialog *d)
{
	if (d->win) {
		werase(d->win);
	}
}

void refresh_dialog(struct dialog *d)
{
	if (d->win) {
		wnoutrefresh(d->win);
	}
}
