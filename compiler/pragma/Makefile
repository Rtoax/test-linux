# SPDX-License-Identifier: GPL-3.0
target-y :=
target-y += GCC_error
target-y += GCC_poison
target-y += GCC_diagnostic
target-y += GCC_dependency
target-y += GCC_system_header
target-y += GCC_target
target-y += GCC_novector
target-y += GCC_unroll
target-y += GCC_ivdep
target-y += pragma-message
target-y += call-func
target-y += push_macro
target-y += message
target-y += _Pragma

include ../compiler.mk

CFLAGS :=
CFLAGS += -Werror=unknown-pragmas
CFLAGS += -I../../
CFLAGS += -pthread

# TODO
CFLAGS_call-func := -Wno-unknown-pragmas
CFLAGS_GCC_system_header := -I./

# Use /etc/os-release file for GCC dependency check, if system upgraded,
# /etc/os-release could be newer than current source code, let's 'Warning',
# not 'error'.
CFLAGS_GCC_dependency := -Wno-error
CFLAGS__Pragma := -Wno-error

CFLAGS_GCC_diagnostic := -pg -Wno-error=pragmas -Wno-error=uninitialized

include ../../template/main.mk

GCC_poison: GCC_poison.o
GCC_diagnostic: GCC_diagnostic.o
GCC_target: GCC_target.o
GCC_error: GCC_error.o
GCC_dependency: GCC_dependency.o
GCC_system_header: GCC_system_header.o
GCC_novector: GCC_novector.o
GCC_ivdep: GCC_ivdep.o
GCC_unroll: GCC_unroll.o
pragma-message: pragma-message.o
call-func: call-func.o
push_macro: push_macro.o
message: message.o
_Pragma: _Pragma.o
