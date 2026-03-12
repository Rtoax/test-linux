# SPDX-License-Identifier: GPL-3.0
include pahole.mk

target-prog-y := version.sh version.sh.1 version.sh.2

PROG_ARGS_version.sh.1 := --major
PROG_ARGS_version.sh.2 := --minor
