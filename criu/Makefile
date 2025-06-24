# SPDX-License-Identifier: GPL-3.0
include ../kconfig.mk

$(info CONFIG_CHECKPOINT_RESTORE = $(CONFIG_CHECKPOINT_RESTORE))

sub-dir :=
TARGETS :=

CFLAGS :=
CFLAGS += -pthread

CFLAGS__GNU_SOURCE :==1
CFLAGS__XOPEN_SOURCE := -D_XOPEN_SOURCE=1

TARGETS_SHELL := check.sh

include ../template/main.mk
