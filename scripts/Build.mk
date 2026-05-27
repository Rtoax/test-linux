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

prog-y := code-count.sh
prog-y += moonlight.sh
prog-y += gotoxy.sh
prog-y += libfile_examples.sh
prog-y += libqemu_examples.sh
prog-y += libso-multiver_examples.sh
prog-y += libstring_examples.sh
prog-y += termplot_examples.sh
prog-y += kconfig_compare.sh
prog-y += kversion.sh kversion.sh.1
prog-y += kcompile.sh kcompile.sh.1
prog-y += patchset_examples.sh
prog-y += qemu-vm_examples.sh
prog-y += runprog_examples.sh

PROG_ARGS_kconfig_compare.sh := --base ../kconfig --config ../kconfig --display all
PROG_ARGS_kversion.sh := short
PROG_ARGS_kversion.sh.1 := full

PROG_ARGS_kcompile.sh.1 := --help
