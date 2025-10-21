# SPDX-License-Identifier: GPL-3.0
target-y :=
target-y += cfsetspeed cfsetospeed cfsetispeed cfgetispeed cfgetospeed
target-y += cfmakeraw
target-y += NCCS
target-y += tcsetattr tcgetattr
target-y += tcgetsid
target-y += password
target-y += set_istrip set_input_mode
target-y += get_cursor_position

CFLAGS += -I../../../
CFLAGS += -lm

target-test-y := test-tcsetattr

include ../../template/main.mk

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

test-tcsetattr:
	echo abcde | ./tcsetattr
