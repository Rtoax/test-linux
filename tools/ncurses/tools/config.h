// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao. All rights reserved. */
#pragma once

#include <ncursesw/curses.h>

#define MY_VERSION "v1.12.9"
#define GIT_REPO "github.com/rtoax/plotcake"

#define KEY_HELP_h "'h': show the help info"
#define KEY_HELP_l "'l': show the label for each line"
#define KEY_HELP_q "'q': quit the plotcake"
#define KEY_HELP_r "'r': reset the ploting"
#define KEY_HELP_s "'s': enable/disable stacked line chart"
#define KEY_HELP_t "'t': change numerical scaling type for paint"
#define KEY_HELP_v "'v': turn on/off the verbose mode"
#define KEY_HELP_x "'x': switch x axis type"
#define KEY_HELP_ENTER "Enter: refresh plot"
#define KEY_HELP_UP "Up: uniform scaling up"
#define KEY_HELP_DOWN "Down: uniform scaling down"
#define KEY_HELP_LEFT "Left: curve shifts to the right"
#define KEY_HELP_RIGHT "Right: curve shifts to the left"

#define EXPIRED_USECS_SHIFT 60000000UL /* 60s, key left, right */
#define EXPIRED_USECS_HELP 1000000UL /* 1s, key h */
#define EXPIRED_USECS_LEGEND 1000000UL /* 1s, key l */

#define ANSI_RED "\033[1;31m"
#define ANSI_GREEN "\033[1;32m"
#define ANSI_YELLOW "\033[1;33m"
#define ANSI_BLUE "\033[1;34m"

#define ANSI_BOLD "\033[1m"
#define ANSI_GRAY "\033[2m"

#define ANSI_RST "\033[m"

#define T_HLINE '-'
#define T_VLINE '|'
#define T_LLCR 'L'
#define T_LARR '<'
#define T_RARR '>'
#define T_UARR '^'
#define T_DARR '`'
#define T_DARR '`'

#define U2500 "─"
#define U2502 "│"
#define U250C "┌"
#define U2510 "┐"
#define U2514 "└"
#define U2518 "┘"
#define U2191 "↑"
#define U2193 "↓"
#define U2192 "→"

#define W_U2502 L"│"

#define U2501 "━"
#define U2503 "┃"
#define U250F "┏"
#define U2513 "┓"
#define U2517 "┗"
#define U251B "┛"
#define U25B2 "▲"
#define U25BC "▼"
#define U25BA "►"
#define U25C4 "◄"

#define W_U2501 L"━"
#define W_U2503 L"┃"
#define W_U250F L"┏"
#define W_U2513 L"┓"
#define W_U2517 L"┗"
#define W_U251B L"┛"
#define W_U25B2 L"▲"
#define W_U25BC L"▼"
#define W_U25BA L"►"
#define W_U25C4 L"◄"

#define U2580 "▀"
#define U2584 "▄"
#define U2588 "█"

#define W_U2580 L"▀"
#define W_U2584 L"▄"
#define W_U2588 L"█"

#define U2665 "♥"
#define W_U2665 L"♥"

#define WCH(W)                                           \
	({                                               \
		cchar_t ___wch;                          \
		setcchar(&___wch, W, A_NORMAL, 0, NULL); \
		___wch;                                  \
	})

#define WCH_U2502 WCH(W_U2502)
#define WCH_U2503 WCH(W_U2503)
#define WCH_U2588 WCH(W_U2588)
#define WCH_U2665 WCH(W_U2665)
