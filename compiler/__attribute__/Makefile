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
TARGETS += alias
TARGETS += always_inline
TARGETS += noinline
TARGETS += cleanup
TARGETS += const
TARGETS += constructor
TARGETS += deprecated
TARGETS += error
TARGETS += format
TARGETS += __gnu_inline__
TARGETS += __naked__
TARGETS += nocf_check
TARGETS += nonnull
TARGETS += noreturn
TARGETS += optimize_omit-frame-pointer
TARGETS += __pure__
TARGETS += randomize_layout
TARGETS += section-initcall
TARGETS += section-readmostly
TARGETS += vector_size
TARGETS += weak
TARGETS += noplt noplt-plt
TARGETS += kernel_helper

TARGETS_todo :=
TARGETS_todo += preserve_access_index

CFLAGS :=

ifeq ($(shell uname -m),x86_64)
  CFLAGS_nocf_check := -fcf-protection
else
  $(warning FIXME: Arch may not support -fcf-protection=full)
endif

CFLAGS_noplt := -DNOPLT=1


.PHONY: build
build: ${TARGETS}
	@echo -e " \033[1;33m Done \033[m"

alias: alias.o
always_inline: always_inline.o
noinline: noinline.o
cleanup: cleanup.o
const: const.o
constructor: constructor.o constructor-obj.o
deprecated: deprecated.o
error: error.o
format: format.o
__gnu_inline__: __gnu_inline__.o
__naked__: __naked__.o
nocf_check: nocf_check.o
nonnull: nonnull.o
noreturn: noreturn.o
optimize_omit-frame-pointer: optimize_omit-frame-pointer.o
__pure__: __pure__.o
randomize_layout: randomize_layout.o
section-initcall: section-initcall.o
section-readmostly: section-readmostly.o
vector_size: vector_size.o
weak: weak.o
noplt: noplt.o
noplt-plt: noplt-plt.o
kernel_helper: kernel_helper.o
preserve_access_index: preserve_access_index.o

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
