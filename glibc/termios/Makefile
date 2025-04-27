# SPDX-License-Identifier: GPL-3.0

CC ?= gcc

TARGETS :=
TARGETS += cfsetspeed cfsetospeed cfsetispeed cfgetispeed cfgetospeed
TARGETS += cfmakeraw
TARGETS += NCCS
TARGETS += tcsetattr tcgetattr
TARGETS += tcgetsid
TARGETS += password
TARGETS += set_istrip set_input_mode
TARGETS += get_cursor_position

CFLAGS += -Werror -Wall
CFLAGS += -I../../../
CFLAGS += -lm
ifdef DEBUG
  CFLAGS += -DDEBUG -O0 -g
endif

include ../../tlbuild.mk

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

termios_helpers.o: termios_helpers.h

cfsetspeed: cfsetspeed.o
cfsetospeed: cfsetospeed.o
cfsetispeed: cfsetispeed.o
cfgetispeed: cfgetispeed.o
cfgetospeed: cfgetospeed.o
cfmakeraw: cfmakeraw.o termios_helpers.o
NCCS: NCCS.o
tcsetattr: tcsetattr.o
tcgetsid: tcgetsid.o
tcgetattr: tcgetattr.o termios_helpers.o
password: password.o
set_istrip: set_istrip.o
set_input_mode: set_input_mode.o
get_cursor_position: get_cursor_position.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) -o $(@) $(^)

test: ${TARGETS}
	@echo -e "  TEST  \033[1;32m$(TARGETS)\033[m"
	echo abcde | ./tcsetattr

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.d *.log
	${Q}rm -rf tmpd-* tmp-*
