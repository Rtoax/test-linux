# SPDX-License-Identifier: GPL-3.0
include ../../bpf/bpf.mk
CC := gcc
CLANG := clang

targets :=
targets-todo :=
targets-bpf :=

targets += __has_builtin
targets += apply_args
targets += apply
targets += bswap16
targets += bswap32
targets += bswap64
targets += clz
targets += constant_p
targets += cpu_supports
targets += expect
targets += frame_address
targets += index
targets += object_size
targets += offsetof
targets += popcount
targets += prefetch
targets += return_address
targets += return_address-2
targets += rindex
targets += thread_pointer
targets += __clear_cache
targets += types_compatible_p
targets += clzl
targets += memcpy
targets += strlen strcmp

targets-bpf += preserve_field_info.bpf.o

targets-todo += read8
targets-todo += va_arg_pack
targets-todo += preserve_enum_value

# TODO: Fix this warning skip
CFLAGS_apply_args := -Wno-incompatible-pointer-types
CFLAGS_popcount := -Wno-int-conversion
# TODO: error: calling ‘__builtin_frame_address’ with a nonzero argument is unsafe
CFLAGS_frame_address := -Wno-error=frame-address
# TODO: error: calling ‘__builtin_return_address’ with a nonzero argument is unsafe
CFLAGS_return_address := -Wno-error=frame-address

# [1] https://gcc.gnu.org/onlinedocs/gcc/BPF-Built-in-Functions.html
#CFLAGS_preserve_field_info := -mxbpf -mco-re

CFLAGS_BPF :=
CFLAGS_BPF += -O2 -g
CFLAGS_BPF += -target bpf
CFLAGS_BPF += $(CFLAG_BPF_TARGET_ARCH)

include ../../template/main.mk

__has_builtin: __has_builtin.o
apply_args: apply_args.o
apply: apply.o
bswap16: bswap16.o
bswap32: bswap32.o
bswap64: bswap64.o
clz: clz.o
constant_p: constant_p.o
cpu_supports: cpu_supports.o
expect: expect.o
frame_address: frame_address.o
index: index.o
object_size: object_size.o
offsetof: offsetof.o
popcount: popcount.o
prefetch: prefetch.o
read8: read8.o
return_address-2: return_address-2.o
return_address: return_address.o
rindex: rindex.o
thread_pointer: thread_pointer.o
va_arg_pack: va_arg_pack.o
__clear_cache: __clear_cache.o
types_compatible_p: types_compatible_p.o
clzl: clzl.o
preserve_enum_value: preserve_enum_value.o
memcpy: memcpy.o
strlen: strlen.o
strcmp: strcmp.o
