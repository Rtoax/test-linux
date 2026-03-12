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

target-prog-y := tcsetattr.sh

CFLAGS += -I../../../
LDFLAGS += -lm
