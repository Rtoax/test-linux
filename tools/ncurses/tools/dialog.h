// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#pragma once
#include <curses.h>
#include <ncurses.h>
#include <panel.h>
#include "config.h"
#include "utils.h"

struct dialog {
	/**
	 * Windows and panels
	 */
	WINDOW *win;
	PANEL *panel;
};

enum win_border_type {
	WIN_BORDER_TYPE_DEFAULT = 0,
	WIN_BORDER_TYPE_UTF8,
};

void new_dialog(struct dialog *d, WINDOW *win);
void del_dialog(struct dialog *d);
void erase_dialog(struct dialog *d);
void refresh_dialog(struct dialog *d);

void set_win_border(WINDOW *win, enum win_border_type type);
