# SPDX-License-Identifier: GPL-3.0
include bpf/bpf.mk

target-y := __has_builtin
target-y += apply_args
target-y += apply
target-y += abs
target-y += bswap16
target-y += bswap32
target-y += bswap64
target-y += clz
target-y += constant_p
target-y += cpu_supports
target-y += exp
target-y += expect
target-y += frame_address
target-y += index
target-y += object_size
target-y += offsetof
target-y += popcount
target-y += prefetch
target-y += return_address
target-y += return_address-2
target-y += rindex
target-y += thread_pointer
target-y += __clear_cache
target-y += types_compatible_p
target-y += clzl
target-y += memcpy
target-y += strlen strcmp
target-y += trap
target-y += nan
target-y += inf
target-y += huge_val
target-y += unreachable

target-bpf-y := preserve_field_info.bpf.o

target-todo := read8
target-todo += va_arg_pack
target-todo += preserve_enum_value

# TODO: Fix this warning skip
CFLAGS_apply_args := -Wno-incompatible-pointer-types
CFLAGS_popcount := -Wno-int-conversion
# TODO: error: calling ‘__builtin_frame_address’ with a nonzero argument is unsafe
CFLAGS_frame_address := -Wno-error=frame-address
# TODO: error: calling ‘__builtin_return_address’ with a nonzero argument is unsafe
CFLAGS_return_address := -Wno-error=frame-address

# [1] https://gcc.gnu.org/onlinedocs/gcc/BPF-Built-in-Functions.html
#CFLAGS_preserve_field_info := -mxbpf -mco-re

CFLAGS_BPF += -O2 -g
CFLAGS_BPF += -target bpf
CFLAGS_BPF += $(bpf-cflags)
