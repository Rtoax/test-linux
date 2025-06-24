TARGETS :=
TARGETS += nostartfiles

LDFLAGS_nostartfiles := -nostartfiles
# /usr/bin/ld: warning: cannot find entry symbol _start; defaulting to 0000000000401000
LDFLAGS_nostartfiles += -lc --entry whatever

include ../../template/main.mk

nostartfiles: nostartfiles.o
