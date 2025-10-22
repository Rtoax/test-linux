OUTPUT := .output/

LLVM_CONFIG = $(shell which llvm-config 2>/dev/null)
LLVM_AS = $(shell which llvm-as 2>/dev/null)
LLVM_DIS = $(shell which llvm-dis 2>/dev/null)
LLC = $(shell which llc 2>/dev/null)

target-y :=
target-y += sum
target-y += sum-avx
target-y += sum-avx2
target-y += cpu-features
target-y += test-asm
target-y += avx512_aux
target-y += mul-avx256
target-y += mul-avx512
target-y += add_pd-avx256
target-y += add_pd-avx512
target-y += add-2dim
target-y += ctrl_flow-f4
target-y += reducetion-f4
target-y += add-unalign-f4
target-y += cvt-df
target-y += mask

target-asm-y := vperm2i128
target-asm-y += vfmadd231ps
target-asm-y += kxord

CFLAGS += -g -ggdb
CFLAGS += -O0

CFLAGS_sum := -DTYPE_FLOAT
CFLAGS_sum-avx := -DTYPE_FLOAT -mavx
CFLAGS_sum-avx2 := -DTYPE_FLOAT -mavx2
CFLAGS_test-asm := -std=gnu11
CFLAGS_avx512_aux := -mavx512f
# Why -mfma?
# - https://www.cnblogs.com/hellowooorld/p/11529078.html
# - https://www.intel.com/content/www/us/en/docs/intrinsics-guide/index.html#text=_mm256_fmaddsub_ps&ig_expand=3191
CFLAGS_mul-avx256 := -mavx2 -mfma
CFLAGS_mul-avx512 := -mavx512f -mfma
CFLAGS_add_pd-avx256 := -mavx2 -mfma
CFLAGS_add_pd-avx512 := -mavx512f -mfma
CFLAGS_add-2dim := -mavx2 -mfma
CFLAGS_ctrl_flow-f4 := -mavx2 -mfma
CFLAGS_reducetion-f4 := -mavx2 -mfma
CFLAGS_add-unalign-f4 := -mavx2 -mfma
CFLAGS_cvt-df := -mavx2 -mfma
CFLAGS_mask := -mavx2 -mavx512f -mfma

include ../../../template/main.mk

sum: ${OUTPUT}sum.o
sum-avx: ${OUTPUT}sum-avx.o
sum-avx2: ${OUTPUT}sum-avx2.o
cpu-features: ${OUTPUT}cpu-features.o
test-asm: ${OUTPUT}test-asm.S.o test-asm.o
avx512_aux: ${OUTPUT}avx512_aux.o
mul-avx256: ${OUTPUT}mul-avx256.o
mul-avx512: ${OUTPUT}mul-avx512.o
add_pd-avx256: ${OUTPUT}add_pd-avx256.o
add_pd-avx512: ${OUTPUT}add_pd-avx512.o
add-2dim: ${OUTPUT}add-2dim.o
ctrl_flow-f4: ${OUTPUT}ctrl_flow-f4.o
reducetion-f4: ${OUTPUT}reducetion-f4.o
add-unalign-f4: ${OUTPUT}add-unalign-f4.o
cvt-df: ${OUTPUT}cvt-df.o
mask: ${OUTPUT}mask.o
vperm2i128: ${OUTPUT}vperm2i128.asm.o
vfmadd231ps: ${OUTPUT}vfmadd231ps.asm.o
kxord: ${OUTPUT}kxord.asm.o

# FIXME: move to main.mk??
ifeq ($(CC),clang)
  # If clang, i want to get IR
  define clang_emit_llvm
    ${Q}$(CC) $(CFLAGS) $(CFLAGS_$(*)) -S -emit-llvm $(1) -o $(1:.c=.ll)
    @$(LLVM_AS) $(1:.c=.ll) -o $(1:.c=.bc)
    @$(LLVM_DIS) $(1:.c=.bc) -o $(1:.c=.dis.ll)
    @$(LLC) $(1:.c=.ll) -o $(1:.c=.llc.s)
  endef
else
  define clang_emit_llvm
  endef
endif
