# SPDX-License-Identifier: GPL-3.0
CC := gcc

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
TARGETS += optimize
TARGETS += optimize_omit-frame-pointer
TARGETS += __pure__
TARGETS += randomize_layout
TARGETS += section-initcall
TARGETS += section-readmostly
TARGETS += vector_size
TARGETS += weak
TARGETS += noplt noplt-plt
TARGETS += kernel_helper
TARGETS += __has_attribute

TARGETS += preserve_access_index

include ../compiler.mk

ifeq ($(CC_-fcf-protection),1)
  CFLAGS_nocf_check := -fcf-protection
else
  $(warning WARNING: ${CC} not support -fcf-protection=full)
endif

CFLAGS_noplt := -DNOPLT=1
CFLAGS_cleanup := -Werror=attributes
CFLAGS_noreturn := -Werror=attributes -Werror
CFLAGS_deprecated := -Wno-error=deprecated-declarations
CFLAGS_format := -Werror=varargs -Werror=attributes
CFLAGS_nonnull := -Wno-error=nonnull -Wno-error=nonnull-compare
CFLAGS___pure__ := -Wno-error=unused-value -Wno-error=unused-variable

include ../../template/main.mk

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
optimize: optimize.o
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
__has_attribute: __has_attribute.o
