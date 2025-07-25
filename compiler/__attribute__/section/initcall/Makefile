targets := main
targets += main-pie

# FIXME: PIE not implement, because _start address in lds
LDFLAGS += -Wl,-Tld-insert-text.lds,-Tld-insert-data.lds
LDFLAGS += -Wl,--no-warn-rwx-segments

CFLAGS_main += -no-pie
LDFLAGS_main += -no-pie
CFLAGS_main-pie := -fpie
LDFLAGS_main-pie := -pie

include ../../../../template/main.mk

main.o: init.h log.h
main: main.o
main-pie.o: init.h log.h
main-pie: main-pie.o
