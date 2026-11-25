// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#pragma once
#include <curses.h>
#include <ncurses.h>
#include <ncursesw/panel.h>

void init_flavor(bool transparent_bg);

chtype getflavor(enum lcolor_enum color);
