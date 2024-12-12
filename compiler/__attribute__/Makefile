# SPDX-License-Identifier: GPL-3.0
SHELL = bash
ifeq ($(V),1)
  Q =
else
  Q = @
  MAKEFLAGS += --no-print-directory
endif
export Q


TARGETS :=
TARGETS += __attribute__alias
TARGETS += __attribute__always_inline
TARGETS += __attribute__noinline
TARGETS += __attribute__cleanup
TARGETS += __attribute__const
TARGETS += __attribute__constructor
TARGETS += __attribute__deprecated
TARGETS += __attribute__error
TARGETS += __attribute__format
TARGETS += __attribute____gnu_inline__
TARGETS += __attribute____naked__
TARGETS += __attribute__nocf_check
TARGETS += __attribute__nonnull
TARGETS += __attribute__noreturn
TARGETS += __attribute__optimize_omit-frame-pointer
TARGETS += __attribute____pure__
TARGETS += __attribute__randomize_layout
TARGETS += __attribute__section-initcall
TARGETS += __attribute__section-readmostly
TARGETS += __attribute__vector_size
TARGETS += __attribute__weak
TARGETS += __attribute__noplt __attribute__noplt-plt
TARGETS += __attribute__kernel_helper

CFLAGS :=

ifeq ($(shell uname -m),x86_64)
  CFLAGS___attribute__nocf_check := -fcf-protection
else
  $(warning FIXME: Arch may not support -fcf-protection=full)
endif

CFLAGS___attribute__noplt := -DNOPLT=1


.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

__attribute__alias: __attribute__alias.o
__attribute__always_inline: __attribute__always_inline.o
__attribute__noinline: __attribute__noinline.o
__attribute__cleanup: __attribute__cleanup.o
__attribute__const: __attribute__const.o
__attribute__constructor: __attribute__constructor.o __attribute__constructor-obj.o
__attribute__deprecated: __attribute__deprecated.o
__attribute__error: __attribute__error.o
__attribute__format: __attribute__format.o
__attribute____gnu_inline__: __attribute____gnu_inline__.o
__attribute____naked__: __attribute____naked__.o
__attribute__nocf_check: __attribute__nocf_check.o
__attribute__nonnull: __attribute__nonnull.o
__attribute__noreturn: __attribute__noreturn.o
__attribute__optimize_omit-frame-pointer: __attribute__optimize_omit-frame-pointer.o
__attribute____pure__: __attribute____pure__.o
__attribute__randomize_layout: __attribute__randomize_layout.o
__attribute__section-initcall: __attribute__section-initcall.o
__attribute__section-readmostly: __attribute__section-readmostly.o
__attribute__vector_size: __attribute__vector_size.o
__attribute__weak: __attribute__weak.o
__attribute__noplt: __attribute__noplt.o
__attribute__noplt-plt: __attribute__noplt-plt.o
__attribute__kernel_helper: __attribute__kernel_helper.o

%.o: %.c
	@echo -e "  CC  \033[1m$(<)\033[m to \033[1m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) -c $(<)
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S $(<) -o $(<:.c=.s)

$(TARGETS): %:
	@echo -e "  LD  \033[1;32m$(@)\033[m"
	${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -o $(@) $(^) $(LDLIBS) $(LDFLAGS) $(LDFLAGS_$(*))

clean:
	@echo -e "  CLEAN  \033[1;32m$(TARGETS)\033[m"
	${Q}rm -f ${TARGETS} *.o *.s
