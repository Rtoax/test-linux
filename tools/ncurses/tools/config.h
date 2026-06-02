// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once

#define MY_VERSION "v1.3.5"

enum lcolor_enum {
	C_GREEN,
	C_RED,
	C_CYAN,
	C_WHITE,
	C_MAGENTA,
	C_BLUE,
	C_YELLOW,
	C_MAX,
	C_UNKNOWN = C_MAX,
};

/* Initial plot boundary */
#define BND_TOP 1
#define BND_BOTTOM 4
#define BND_LEFT 7
#define BND_RIGHT 6

/* TODO: support more line type */
#ifdef NOACS
#define T_HLINE '-'
#define T_VLINE '|'
#define T_LLCR 'L'
#define T_RARR '>'
#define T_UARR '^'
#else
#define T_HLINE ACS_HLINE
#define T_VLINE ACS_VLINE
#define T_LLCR ACS_LLCORNER
#define T_RARR ACS_RARROW
#define T_UARR ACS_UARROW
#endif

#define U2500 "─"
#define U2502 "│"
#define U250C "┌"
#define U2510 "┐"
#define U2514 "└"
#define U2518 "┘"

#define W_U2502 L"│"

#define U2501 "━"
#define U2503 "┃"
#define U250F "┏"
#define U2513 "┓"
#define U2517 "┗"
#define U251B "┛"
#define U25B2 "▲"
#define U25BA "►"
#define U25C4 "◄"

#define W_U2501 L"━"
#define W_U2503 L"┃"
#define W_U250F L"┏"
#define W_U2513 L"┓"
#define W_U2517 L"┗"
#define W_U251B L"┛"
#define W_U25B2 L"▲"
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
