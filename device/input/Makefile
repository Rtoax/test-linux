# SPDX-License-Identifier: GPL-3.0
SHELL = bash
include ../../tlbuild.mk


TARGETS :=
TARGETS += mice mouse0
TARGETS += event0 keyboard

CFLAGS :=

CFLAGS_mouse0 := -DDEV_INPUT_MOUSE0=1

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

mice: mice.o
mouse0: mouse0.o
event0: event0.o
keyboard: keyboard.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))
	$(call user_strip,$(@))

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d
