# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS :=
TARGETS += cfsetspeed cfsetospeed cfsetispeed cfgetispeed cfgetospeed
TARGETS += cfmakeraw
TARGETS += NCCS
TARGETS += tcsetattr tcgetattr
TARGETS += tcgetsid
TARGETS += password
TARGETS += set_istrip set_input_mode

CC = gcc

CFLAGS := -Werror -Wall
CFLAGS += -I../../../
CFLAGS += -lm
CFLAGS += -DDEBUG -O0 -g

build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

cfsetspeed: cfsetspeed.o
cfsetospeed: cfsetospeed.o
cfsetispeed: cfsetispeed.o
cfgetispeed: cfgetispeed.o
cfgetospeed: cfgetospeed.o
cfmakeraw: cfmakeraw.o helpers.o
NCCS: NCCS.o
tcsetattr: tcsetattr.o
tcgetsid: tcgetsid.o
tcgetattr: tcgetattr.o helpers.o
password: password.o
set_istrip: set_istrip.o
set_input_mode: set_input_mode.o

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
