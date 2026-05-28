include ncurses.mk

target-y += loadavg
target-y += loadavg.dbg

prog-y += examples.sh

loadavg-objs := value.o plot.o ram.o stdin.o lines.o
loadavg.dbg-objs := loadavg.1.o value.o plot.o ram.o stdin.o lines.o

CFLAGS_loadavg.1 := -DDEBUG=1

LDFLAGS += ${ncurses-ldflags}
