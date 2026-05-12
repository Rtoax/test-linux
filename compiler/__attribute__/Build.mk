# SPDX-License-Identifier: GPL-3.0
include clang.mk
include compiler.mk

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
target-y += visibility
target-y += packed

target-bpf-${HAVE_CLANG} := preserve_access_index.bpf.o

ifeq ($(feature-fcf-protection),y)
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
