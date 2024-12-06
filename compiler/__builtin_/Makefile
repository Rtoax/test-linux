SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS :=
TARGETS += __builtin_apply_args
TARGETS += __builtin_apply
TARGETS += __builtin_bswap16
TARGETS += __builtin_bswap32
TARGETS += __builtin_bswap64
TARGETS += __builtin_clz
TARGETS += __builtin_constant_p
TARGETS += __builtin_cpu_supports
TARGETS += __builtin_expect
TARGETS += __builtin_frame_address
TARGETS += __builtin_index
TARGETS += __builtin_object_size
TARGETS += __builtin_offsetof
TARGETS += __builtin_popcount
TARGETS += __builtin_prefetch
TARGETS += __builtin_return_address-2
TARGETS += __builtin_return_address
TARGETS += __builtin_rindex
TARGETS += __builtin_thread_pointer
TARGETS += __builtin___clear_cache
TARGETS += __builtin_types_compatible_p
TARGETS += __builtin_clzl

TARGETS_todo += __builtin_preserve_field_info
TARGETS_todo += __builtin_read8
TARGETS_todo += __builtin_va_arg_pack

CC = gcc

# TODO: Fix this warning skip
CFLAGS___builtin_apply_args := -Wno-incompatible-pointer-types
CFLAGS___builtin_popcount := -Wno-int-conversion

build: ${TARGETS}

__builtin_apply_args: __builtin_apply_args.o
__builtin_apply: __builtin_apply.o
__builtin_bswap16: __builtin_bswap16.o
__builtin_bswap32: __builtin_bswap32.o
__builtin_bswap64: __builtin_bswap64.o
__builtin_clz: __builtin_clz.o
__builtin_constant_p: __builtin_constant_p.o
__builtin_cpu_supports: __builtin_cpu_supports.o
__builtin_expect: __builtin_expect.o
__builtin_frame_address: __builtin_frame_address.o
__builtin_index: __builtin_index.o
__builtin_object_size: __builtin_object_size.o
__builtin_offsetof: __builtin_offsetof.o
__builtin_popcount: __builtin_popcount.o
__builtin_prefetch: __builtin_prefetch.o
__builtin_preserve_field_info: __builtin_preserve_field_info.o
__builtin_read8: __builtin_read8.o
__builtin_return_address-2: __builtin_return_address-2.o
__builtin_return_address: __builtin_return_address.o
__builtin_rindex: __builtin_rindex.o
__builtin_thread_pointer: __builtin_thread_pointer.o
__builtin_va_arg_pack: __builtin_va_arg_pack.o
__builtin___clear_cache: __builtin___clear_cache.o
__builtin_types_compatible_p: __builtin_types_compatible_p.o
__builtin_clzl: __builtin_clzl.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) -o $(@) -c $(<) $(CFLAGS) $(CFLAGS_$(*))

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*)) $(CFLAGS) $(CFLAGS_$(*))

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o
