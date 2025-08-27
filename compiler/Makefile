# SPDX-License-Identifier: GPL-3.0
include ../template/ansi.mk
include ../gnu/gnu.mk

sub-dir := annobin
sub-dir += ast
sub-dir += linker
sub-dir += llvm
sub-dir += jit
sub-dir += __atomic
sub-dir += __attribute__
sub-dir += __builtin_
sub-dir += dwarf
sub-dir += foption option
sub-dir += machine-option
sub-dir += openacc
sub-dir += openmp
sub-dir += optimize
sub-dir += pragma
sub-dir += reloc
sub-dir += specs
sub-dir += __sync
sub-dir += Wwarn

targets := __GNUC__
targets += __GNUC_PREREQ
targets += __VERSION__

targets-prep := $(CC)-macros.h

include compiler.mk

include ../template/main.mk

$(CC)-macros.h:
	$(call log_tgt_exe,HDR,,$(@))
	$(call gen_compiler_macro_hdr,$(@))

__VERSION__: __VERSION__.o
__GNUC__: __GNUC__.o
__GNUC_PREREQ: __GNUC_PREREQ.o
