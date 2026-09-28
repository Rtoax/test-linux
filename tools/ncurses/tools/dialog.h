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

void new_dialog(struct dialog *d, WINDOW *win);
void del_dialog(struct dialog *d);
void erase_dialog(struct dialog *d);
void refresh_dialog(struct dialog *d);
