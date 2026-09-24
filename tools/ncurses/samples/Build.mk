include ncurses.mk

target-y += alert
target-y += attributes
target-y += color
target-y += getch
target-y += getmaxyx
target-y += keyname
target-y += initscr
target-y += mouse
target-y += newwin
target-y += setlocale

CFLAGS_mouse := -DTEST_MOUSE=1

LDFLAGS += -pthread
LDFLAGS += ${ncurses-ldflags}
LDFLAGS_alert += -lpanel

prog-y += alert
prog-y += newwin
