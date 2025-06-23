# SPDX-License-Identifier: GPL-3.0
TARGETS :=
TARGETS += overwrite-plt

CFLAGS := -Werror -Wall -D_GNU_SOURCE
CFLAGS_overwrite-plt := -DOVERWRITE=1

include ../../template/main.mk

overwrite-plt: overwrite-plt.o
