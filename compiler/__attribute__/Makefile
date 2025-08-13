# SPDX-License-Identifier: GPL-3.0
targets :=
targets += alias
targets += always_inline
targets += noinline
targets += cleanup
targets += const
targets += constructor
targets += deprecated
targets += error
targets += format
targets += __gnu_inline__
targets += __naked__
targets += nocf_check
targets += nonnull
targets += noreturn
targets += optimize
targets += optimize_omit-frame-pointer
targets += __pure__
targets += randomize_layout
targets += section-initcall
targets += section-readmostly
targets += vector_size
targets += weak
targets += noplt noplt-plt
targets += kernel_helper
targets += __has_attribute

targets-bpf := preserve_access_index.bpf.o

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
__has_attribute: __has_attribute.o
