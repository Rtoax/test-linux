# SPDX-License-Identifier: GPL-3.0
include ansi.mk
include gnu.mk

subdir-y := annobin
subdir-y += ast
subdir-y += bison
subdir-y += gnu
subdir-y += linker
subdir-y += llvm
subdir-y += jit
subdir-y += __atomic
subdir-y += __attribute__
subdir-y += __builtin_
subdir-y += dwarf
subdir-y += foption option
subdir-y += machine-option
subdir-y += openacc
subdir-y += openmp
subdir-y += optimize
subdir-y += pragma
subdir-y += reloc
subdir-y += specs
subdir-y += __sync
subdir-y += Wwarn

target-y := __GNUC__
target-y += __GNUC_PREREQ
target-y += __VERSION__

target-shell-y := info.sh

target-prep-y := $(CC)-macros.h

include compiler.mk

include main.mk

$(CC)-macros.h:
	$(call log_exe,HDR,$(@))
	$(call gen_compiler_macro_hdr,$(@))

__VERSION__: __VERSION__.o
__GNUC__: __GNUC__.o
__GNUC_PREREQ: __GNUC_PREREQ.o
