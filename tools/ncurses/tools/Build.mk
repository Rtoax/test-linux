include ncurses.mk

target-y += loadavg
target-y += loadavg.dbg

prog-y += examples.sh

loadavg-objs := value.o plot.o ram.o stdin.o lines.o
loadavg.dbg-objs := loadavg.1.o value.1.o plot.1.o ram.1.o stdin.1.o lines.1.o

$(foreach obj, loadavg value plot ram stdin lines, \
  $(eval CFLAGS_${obj}.1 := -DDEBUG=1))

LDFLAGS += ${ncurses-ldflags}
