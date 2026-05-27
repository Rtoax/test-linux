// SPDX-License-Identifier: (LGPL-2.1 OR BSD-2-Clause)
/* Copyright (C) 2026 Rong Tao */
#pragma once

enum {
	C_GREEN,
	C_RED,
	C_CYAN,
	C_WHITE,
	C_MAGENTA,
	C_BLUE,
	C_YELLOW,
	C_MAX,
};

#define BND_TOP 1
#define BND_BOTTOM 4
#define BND_LEFT 7
#define BND_RIGHT 6

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

#define WCH(W)                                           \
	({                                               \
		cchar_t ___wch;                          \
		setcchar(&___wch, W, A_NORMAL, 0, NULL); \
		___wch;                                  \
	})

#define WCH_U2503 WCH(W_U2503)
