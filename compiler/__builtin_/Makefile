# SPDX-License-Identifier: GPL-3.0
include ../../tlbuild.mk
include ../../bpf/bpf.mk

CC := gcc
CLANG := clang

TARGETS :=
TARGETS_todo :=
TARGETS_BPF :=

TARGETS += __has_builtin
TARGETS += apply_args
TARGETS += apply
TARGETS += bswap16
TARGETS += bswap32
TARGETS += bswap64
TARGETS += clz
TARGETS += constant_p
TARGETS += cpu_supports
TARGETS += expect
TARGETS += frame_address
TARGETS += index
TARGETS += object_size
TARGETS += offsetof
TARGETS += popcount
TARGETS += prefetch
TARGETS += return_address-2
TARGETS += return_address
TARGETS += rindex
TARGETS += thread_pointer
TARGETS += __clear_cache
TARGETS += types_compatible_p
TARGETS += clzl
TARGETS += memcpy
TARGETS += strlen strcmp

TARGETS_BPF += preserve_field_info.bpf.o

TARGETS_todo += read8
TARGETS_todo += va_arg_pack
TARGETS_todo += preserve_enum_value

# TODO: Fix this warning skip
CFLAGS_apply_args := -Wno-incompatible-pointer-types
CFLAGS_popcount := -Wno-int-conversion

# [1] https://gcc.gnu.org/onlinedocs/gcc/BPF-Built-in-Functions.html
#CFLAGS_preserve_field_info := -mxbpf -mco-re

CFLAGS_BPF :=
CFLAGS_BPF += -O2 -g
CFLAGS_BPF += -target bpf
CFLAGS_BPF += $(CFLAG_BPF_TARGET_ARCH)

.PHONY: build
build: $(TARGETS) $(TARGETS_BPF)
	@echo -e " \033[1;33m Done \033[m"

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

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

%.bpf.o: %.c
	@echo -e "  BPF  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CLANG) -c $(<) -o $(@) ${CFLAGS_BPF} $(CFLAGS_BPF_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS) $(TARGETS_BPF)\033[m"
	${Q}rm -f ${TARGETS} ${TARGETS_BPF} *.o
