# SPDX-License-Identifier: GPL-3.0
target-y += cfsetspeed cfsetospeed cfsetispeed cfgetispeed cfgetospeed
target-y += cfmakeraw
target-y += NCCS
target-y += tcsetattr tcgetattr
target-y += tcgetsid
target-y += password
target-y += set_istrip set_input_mode
target-y += get_cursor_position

cfmakeraw-objs := termios_helpers.o
tcgetattr-objs := termios_helpers.o

target-test-y := test-tcsetattr

CFLAGS += -I../../../
LDFLAGS += -lm

include main.mk

test-tcsetattr:
	echo abcde | ./tcsetattr
