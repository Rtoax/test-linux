# SPDX-License-Identifier: GPL-3.0
include compiler.mk
include glibc.mk
include dir.mk
include sudo.mk
include cpu.mk
include os.mk

subdir-y += docs
subdir-y += git
subdir-y += rootfs
subdir-y += version

target-prog-y := code-count.sh
target-prog-y += moonlight.sh
target-prog-y += gotoxy.sh
target-prog-y += libfile_examples.sh
target-prog-y += libqemu_examples.sh
target-prog-y += libso-multiver_examples.sh
target-prog-y += libstring_examples.sh
target-prog-y += termplot_examples.sh
target-prog-y += kconfig_compare.sh
target-prog-y += kversion.sh kversion.sh.1
target-prog-y += patchset_examples.sh
target-prog-y += qemu-vm.sh
target-prog-y += runprog_examples.sh

PROG_ARGS_kconfig_compare.sh := --base ../kconfig --config ../kconfig --display all
PROG_ARGS_kversion.sh := short
PROG_ARGS_kversion.sh.1 := full
