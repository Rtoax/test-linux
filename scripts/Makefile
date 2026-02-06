# SPDX-License-Identifier: GPL-3.0
include compiler.mk
include glibc.mk
include ansi.mk
include dir.mk
include sudo.mk
include cpu.mk
include os.mk

subdir-y := git

target-shell-y := moonlight.sh
target-shell-y += gotoxy.sh
target-shell-y += termplot_examples.sh
target-shell-y += kconfig_compare.sh
target-shell-y += kversion.sh
target-shell-y += patchset_examples.sh

SHELL_ARGS_kconfig_compare.sh := --base ../kconfig --config ../kconfig --display all
SHELL_ARGS_kversion.sh := short

include main.mk
