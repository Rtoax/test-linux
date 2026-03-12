# SPDX-License-Identifier: GPL-3.0
OUTPUT := .output/
__IGNORE_NOTFOUND_ERROR__ := 1

include os.mk
include nvidia/cuda.mk
include amd/rocm.mk
include cestc/luca.mk
include metax/hpcc.mk
include compiler.mk

common-objs-y := fp4
common-objs-y += fp6
common-objs-y += fp8
common-objs-y += half
common-objs-y += bfloat16
common-objs-y += complex
common-objs-y += float
common-objs-y += double
common-objs-${CC__Float128} += fp128
common-objs-y += int
common-objs-y += simd

target-nvcc-${HAVE_CUDA} := $(common-objs-y)

target-post-${HAVE_CUDA} += $(patsubst %,${OUTPUT}%.E.cu,$(target-nvcc-y))
target-post-${HAVE_CUDA} += $(patsubst %,${OUTPUT}%.cu.ptx,$(target-nvcc-y))
target-post-${HAVE_CUDA} += $(patsubst %,${OUTPUT}%.cu.cpp.ii,$(target-nvcc-y))

target-hipcc-${HAVE_HIP} := $(patsubst %,%-hip,$(common-objs-y))
target-htcc-${HAVE_HPCC} := $(patsubst %,%-hpcc,$(common-objs-y))

target-lscc-${HAVE_LUCA} := $(patsubst %,%-luca,$(common-objs-y))

# Skip warnings
# warning: designated initializers are a C++20 extension [-Wc++20-designator]
# warning: brace elision for designated initializer is a C99 extension [-Wc99-designator]
CFLAGS_HIPCC_half := -Wno-c99-designator -Wno-c++20-designator

common-cflags := ${cflags-support-types-y} -I..
# FIXME and TODO: I just install cuda13.0 on fedora 43, but cuda13.0 not support
# fedora43 yet. If cuda support fedora43, then could remove OS_CFLAGS.
# see commit c10a95f14208 ("cuda13.0: skip compile error on fedora 43")
common-cflags += ${OS_CFLAGS}

CFLAGS_HIPCC := ${common-cflags}
CFLAGS_HTCC := ${common-cflags}
CFLAGS_LSCC := ${common-cflags}
CFLAGS_NVCC := ${common-cflags}
