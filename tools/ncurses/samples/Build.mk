include ncurses.mk

target-y += getch
target-y += getmaxyx
target-y += keyname
target-y += initscr
target-y += mouse
target-y += setlocale

CFLAGS_mouse := -DTEST_MOUSE=1

LDFLAGS += -pthread
LDFLAGS += ${ncurses-ldflags}
