# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/

target-y :=
target-y += alias
target-y += always_inline
target-y += noinline
target-y += cleanup
target-y += const
target-y += constructor
target-y += deprecated
target-y += error
target-y += format
target-y += __gnu_inline__
target-y += __naked__
target-y += nocf_check
target-y += nonnull
target-y += noreturn
target-y += optimize
target-y += optimize_omit-frame-pointer
target-y += __pure__
target-y += randomize_layout
target-y += section-initcall
target-y += section-readmostly
target-y += vector_size
target-y += weak
target-y += noplt noplt-plt
target-y += kernel_helper
target-y += __has_attribute
target-y += __mode__
target-y += no_instrument_function

target-bpf-y := preserve_access_index.bpf.o

include ../compiler.mk

ifeq ($(CC_-fcf-protection),y)
  CFLAGS_nocf_check := -fcf-protection
else
  $(warning WARNING: ${CC} not support -fcf-protection=full)
endif

CFLAGS_noplt := -DNOPLT=1
CFLAGS_cleanup := -Werror=attributes
CFLAGS_noreturn := -Werror=attributes -Werror
CFLAGS_deprecated := -Wno-error=deprecated-declarations
CFLAGS_format := -Werror=varargs -Werror=attributes
CFLAGS_nonnull := -Wno-error=nonnull
CFLAGS___pure__ := -Wno-error=unused-value -Wno-error=unused-variable
# FIXME: error: ‘naked’ attribute directive ignored
CFLAGS___naked__ := -Wno-error=attributes

ifeq ($(CC),clang)
  CFLAGS_nonnull += -Wno-error=tautological-pointer-compare
  CFLAGS_section-initcall := -Wno-error=ordered-compare-function-pointers
else
  # clang error: unknown warning option '-Werror=nonnull-compare'
  CFLAGS_nonnull += -Wno-error=nonnull-compare
endif

CFLAGS_no_instrument_function := -pg -DTEST_MAIN=1
CFLAGS_no_instrument_function += -Wno-error=frame-address

include ../../template/main.mk

alias: ${OUTPUT}alias.o
always_inline: ${OUTPUT}always_inline.o
noinline: ${OUTPUT}noinline.o
cleanup: ${OUTPUT}cleanup.o
const: ${OUTPUT}const.o
constructor: ${OUTPUT}constructor.o ${OUTPUT}constructor-obj.o
deprecated: ${OUTPUT}deprecated.o
error: ${OUTPUT}error.o
format: ${OUTPUT}format.o
__gnu_inline__: ${OUTPUT}__gnu_inline__.o
__naked__: ${OUTPUT}__naked__.o
nocf_check: ${OUTPUT}nocf_check.o
nonnull: ${OUTPUT}nonnull.o
noreturn: ${OUTPUT}noreturn.o
optimize: ${OUTPUT}optimize.o
optimize_omit-frame-pointer: ${OUTPUT}optimize_omit-frame-pointer.o
__pure__: ${OUTPUT}__pure__.o
randomize_layout: ${OUTPUT}randomize_layout.o
section-initcall: ${OUTPUT}section-initcall.o
section-readmostly: ${OUTPUT}section-readmostly.o
vector_size: ${OUTPUT}vector_size.o
weak: ${OUTPUT}weak.o
noplt: ${OUTPUT}noplt.o
noplt-plt: ${OUTPUT}noplt-plt.o
kernel_helper: ${OUTPUT}kernel_helper.o
__has_attribute: ${OUTPUT}__has_attribute.o
__mode__: ${OUTPUT}__mode__.o
no_instrument_function: ${OUTPUT}no_instrument_function.o
