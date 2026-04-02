# SPDX-License-Identifier: GPL-3.0
include nvidia/cuda.mk
include amd/rocm.mk
include metax/hpcc.mk
include cestc/luca.mk

subdir-y := samples
subdir-y += blas
subdir-y += dnn
subdir-y += fft
subdir-y += file
subdir-y += pti
subdir-y += ptx
subdir-y += rand
subdir-y += sparse
subdir-y += solver
subdir-y += vpu
subdir-y += intrinsics
subdir-y += fakeCUDA
