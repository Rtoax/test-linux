include ncurses.mk

target-y += getch
target-y += getmaxyx
target-y += initscr
target-y += setlocale

LDFLAGS += ${ncurses-ldflags}
