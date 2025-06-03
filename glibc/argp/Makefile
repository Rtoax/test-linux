# SPDX-License-Identifier: GPL-3.0
TARGETS :=
TARGETS += argp_parse

CFLAGS := -Werror -Wall
CFLAGS += -D_GNU_SOURCE

LDFLAGS := -pthread -lrt

include ../../template/main.mk

argp_parse: argp_parse.o
