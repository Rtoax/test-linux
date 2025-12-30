# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

include ansi.mk
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

CFLAGS_BPF :=
CFLAGS_BPF += -O2 -g
CFLAGS_BPF += -target bpf
CFLAGS_BPF += $(CFLAG_BPF_TARGET_ARCH)

include main.mk

__has_builtin: ${OUTPUT}__has_builtin.o
apply_args: ${OUTPUT}apply_args.o
apply: ${OUTPUT}apply.o
bswap16: ${OUTPUT}bswap16.o
bswap32: ${OUTPUT}bswap32.o
bswap64: ${OUTPUT}bswap64.o
clz: ${OUTPUT}clz.o
constant_p: ${OUTPUT}constant_p.o
cpu_supports: ${OUTPUT}cpu_supports.o
exp: ${OUTPUT}exp.o
expect: ${OUTPUT}expect.o
frame_address: ${OUTPUT}frame_address.o
index: ${OUTPUT}index.o
object_size: ${OUTPUT}object_size.o
offsetof: ${OUTPUT}offsetof.o
popcount: ${OUTPUT}popcount.o
prefetch: ${OUTPUT}prefetch.o
read8: ${OUTPUT}read8.o
return_address-2: ${OUTPUT}return_address-2.o
return_address: ${OUTPUT}return_address.o
rindex: ${OUTPUT}rindex.o
thread_pointer: ${OUTPUT}thread_pointer.o
va_arg_pack: ${OUTPUT}va_arg_pack.o
__clear_cache: ${OUTPUT}__clear_cache.o
types_compatible_p: ${OUTPUT}types_compatible_p.o
clzl: ${OUTPUT}clzl.o
preserve_enum_value: ${OUTPUT}preserve_enum_value.o
memcpy: ${OUTPUT}memcpy.o
strlen: ${OUTPUT}strlen.o
strcmp: ${OUTPUT}strcmp.o
trap: ${OUTPUT}trap.o
abs: ${OUTPUT}abs.o
nan: ${OUTPUT}nan.o
inf: ${OUTPUT}inf.o
huge_val: ${OUTPUT}huge_val.o
unreachable: ${OUTPUT}unreachable.o
