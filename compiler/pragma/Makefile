# SPDX-License-Identifier: GPL-3.0
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

include compiler.mk

CFLAGS += -Werror=unknown-pragmas
CFLAGS += -I../../

# TODO
CFLAGS_call-func := -Wno-unknown-pragmas
CFLAGS_GCC_system_header := -I./

# Use /etc/os-release file for GCC dependency check, if system upgraded,
# /etc/os-release could be newer than current source code, let's 'Warning',
# not 'error'.
CFLAGS_GCC_dependency := -Wno-error
CFLAGS__Pragma := -Wno-error

CFLAGS_GCC_diagnostic := -pg -Wno-error=pragmas -Wno-error=uninitialized

include main.mk
